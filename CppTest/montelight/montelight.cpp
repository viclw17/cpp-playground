// ==Montelight==
// Tegan Brennan, Stephen Merity, Taiyo Wilson
#include <cmath>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "vector.h"
#include "ray.h"
#include "image.h"
#include "shape.h"
#include "sphere.h"
#include "tracer.h"

using namespace std;

// Set up our testing scenes
// They're all Cornell box inspired: http://graphics.ucsd.edu/~henrik/images/cbox.html
/////////////////////////
// Scene format: Sphere(position, radius, color, emission)
/////////////////////////
std::vector<Shape *> simpleScene = {
  // Left sphere
  new Sphere(Vector(1e5+1,40.8,81.6), 1e5f, Vector(.75,.25,.25), Vector()),
  // Right sphere
  new Sphere(Vector(-1e5+99,40.8,81.6), 1e5f, Vector(.25,.25,.75), Vector()),
  // Back sphere
  new Sphere(Vector(50,40.8, 1e5), 1e5f, Vector(.75,.75,.75), Vector()),
  // Floor sphere
  new Sphere(Vector(50, 1e5, 81.6), 1e5f, Vector(.75,.75,.75), Vector()),
  // Roof sphere
  new Sphere(Vector(50,-1e5+81.6,81.6), 1e5f, Vector(.75,.75,.75), Vector()),
  // Traditional mirror sphere
  new Sphere(Vector(27,16.5,47), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  // Traditional glass sphere
  new Sphere(Vector(73,16.5,78), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  // Light source
  //new Sphere(Vector(50,681.6-.27,81.6), 600, Vector(1,1,1) * 0.5, Vector(12,12,12))
  new Sphere(Vector(50,65.1,81.6), 8.5, Vector(), Vector(4,4,4) * 100) // Small = 1.5, Large = 8.5
};
/////////////////////////
std::vector<Shape *> complexScene = {
  new Sphere(Vector(1e5+1,40.8,81.6), 1e5f, Vector(.75,.25,.25), Vector()), // Left
  new Sphere(Vector(-1e5+99,40.8,81.6), 1e5f, Vector(.25,.25,.75), Vector()), // Right
  new Sphere(Vector(50,40.8, 1e5), 1e5f, Vector(.75,.75,.75), Vector()), // Back
  new Sphere(Vector(50, 1e5, 81.6), 1e5f, Vector(.75,.75,.75), Vector()), //Bottom
  new Sphere(Vector(50,-1e5+81.6,81.6), 1e5f, Vector(.75,.75,.75), Vector()), // Top
  new Sphere(Vector(20,16.5,40), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  new Sphere(Vector(50,16.5,80), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  new Sphere(Vector(75,16.5,120), 16.5f, Vector(1,1,1) * 0.799, Vector()),
  new Sphere(Vector(50,65.1,40), 1.5, Vector(), Vector(4,4,4) * 100), // Light
  new Sphere(Vector(50,65.1,120), 1.5, Vector(), Vector(4,4,4) * 100), // Light
};
//

int main(int argc, const char *argv[]) {
    /////////////////////////
    // Variables to modify the process or the images
    //  EMITTER_SAMPLING = true;
    int w = 256, h = 256;
    // w=512; h=512;
    int SNAPSHOT_INTERVAL = 100;
    unsigned int SAMPLES = 100;//50;//100;
    bool FOCUS_EFFECT = false;
    double FOCAL_LENGTH = 35;
    double APERTURE_FACTOR = 1; // ratio of original/new aperture
    //(>1: smaller view angle, <1: larger view angle)
    // Initialize the image
    Image img(w, h);

    /////////////////////////
    // Set which scene should be raytraced
    auto &scene = simpleScene;// complexScene;
    Tracer tracer = Tracer(scene);

    /////////////////////////
    // Set up the camera
    double aperture = 0.5135 / APERTURE_FACTOR;
    Vector cx = Vector((w * aperture) / h, 0, 0);
    Vector dir_norm = Vector(0, -0.042612, -1).norm();//x,y,z
    double L = 140;
    double L_new = APERTURE_FACTOR * L;
    double L_diff = L - L_new;
    Vector cam_shift = dir_norm * (L_diff);
    if (L_diff < 0){cam_shift = cam_shift * 1.5;}
    L = L_new;
    Ray camera = Ray(Vector(50, 52, 295.6) + cam_shift, dir_norm);
    // Cross product gets the vector perpendicular to cx and the "gaze" direction
    Vector cy = (cx.cross(camera.direction)).norm() * aperture;

    /////////////////////////
    // Take a set number of samples per pixel
    for (int sample = 0; sample < SAMPLES; ++sample) {
    std::cout << "Taking sample " << sample << "\r" << std::flush;
        if (sample && sample % SNAPSHOT_INTERVAL == 0) {
            std::ostringstream fn;
            fn << std::setfill('0') << std::setw(5) << sample;
//             cout << fn.str() << endl;
            img.save("render_" + fn.str());
        }
    // For each pixel, sample a ray in that direction
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
        /*
        Vector target = img.getPixel(x, y);
        double A = (target - img.getSurroundingAverage(x, y, sample % 2)).abs().max() / (100 / 255.0);
        if (sample > 10 && drand48() > A) {
          continue;
        }
        ++updated;
        */
        // Jitter pixel randomly in dx and dy according to the tent filter
        double Ux = 2 * drand48();
        double Uy = 2 * drand48();
        double dx;
        if (Ux < 1) {
          dx = sqrt(Ux) - 1;
        } else {
          dx = 1 - sqrt(2 - Ux);
        }
        double dy;
        if (Uy < 1) {
          dy = sqrt(Uy) - 1;
        } else {
          dy = 1 - sqrt(2 - Uy);
        }
          
        // Calculate the direction of the camera ray
        Vector d = (cx * (((x+dx) / float(w)) - 0.5)) + (cy * (((y+dy) / float(h)) - 0.5)) + camera.direction;
        Ray ray = Ray(camera.origin + d * 140, d.norm());
            
        // If we're actually using depth of field, we need to modify the camera ray to account for that
        if (FOCUS_EFFECT) {
          // Calculate the focal point
          Vector fp = (camera.origin + d * L) + d.norm() * FOCAL_LENGTH;
          // Get a pixel point and new ray direction to calculate where the rays should intersect
          Vector del_x = (cx * dx * L / float(w));
          Vector del_y = (cy * dy * L / float(h));
          Vector point = camera.origin + d * L;
          point = point + del_x + del_y;
          d = (fp - point).norm();
          ray = Ray(camera.origin + d * L, d.norm());
        }
            
        // Retrieve the radiance of the given hit location (i.e. brightness of the pixel)
        Vector rads = tracer.getRadiance(ray, 0);
        // Clamp the radiance so it is between 0 and 1
        // If we don't do this, antialiasing doesn't work properly on bright lights
        rads.clamp();
        // Add result of sample to image
        img.setPixel(x, y, rads);
        }
    }
    }
    // Save the resulting raytraced image
    img.save("render");
    return 0;
}
