#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

#define M_PI 3.1416

static int const _size = 256;
static int const mask = _size - 1;
int perm[_size];
float grads_x[_size], grads_y[_size];

// produce random perm array and random gradients(x direction and y direction!)
void init() {
	for (int index = 0; index < _size; ++index) {
		int other = rand() % (index + 1);
		if (index > other)
			perm[index] = perm[other];
		perm[other] = index;
		grads_x[index] = cosf(2.0f * M_PI * index / _size); //x direction
		grads_y[index] = sinf(2.0f * M_PI * index / _size); //y direction
		// grads_x[hash], grads_y[hash] combined produce a random vector
	}
}

float f(float t) {
	t = fabsf(t); // float fabsf( float arg );
	return t >= 1.0f ? 0.0f : (1.0f - (3.0f - 2.0f * t) * t * t);
}
float surflet(float x, float y, float grad_x, float grad_y) {
	//return (x + 1)*.5; // dont do (x + 1)/2
	//return (((x + 1)*.5)+((y + 1)*.5))*.5;
	//x = x * 2 - 1;
	//y = y * 2 - 1;
	//return f(x);
	//return f(x) * f(y);
	//return f(x) * f(y) * (x + y);
	return f(x) * f(y) * (grad_x * x + grad_y * y); // dot product!!!
}
float noise(float x, float y) {
	float result = 0.0f;
	int cell_x = floorf(x); //0,1,2,...,space
	int cell_y = floorf(y); //0,1,2,...,space
	for (int grid_y = cell_y; grid_y <= cell_y + 1; ++grid_y)
		for (int grid_x = cell_x; grid_x <= cell_x + 1; ++grid_x) {
			// random hash
			int hash = perm[(perm[grid_x & mask] + grid_y) & mask];
			// x - grid_x is similar to fract()
			// x - grid_x, y - grid_y can be negative
			result += surflet(x - grid_x, y - grid_y, grads_x[hash], grads_y[hash]); // debug: abs(x - grid_x) always 0 or 1, so f(x - grid_x) always 0, so surflet always 0!
		}
	return result;
}


int main() {
    init();
    const int dimension = 100;

    ofstream outfile("render.pgm", ios_base::out);
    outfile << "P2\n" << dimension << " " << dimension << "\n255\n";

    int lattice = 10;
    int space = dimension / float(lattice);
    for (int j = 0; j < dimension; j++) {
        float y = (float)j / ((float)space); // cast to float!!!
        for (int i = 0; i < dimension; i++) {
            float x = (float)i / ((float)space);

            float n;
            if (i % 10 == 0 || j % 10 == 0 /*|| i == dimension-1 || j == dimension-1*/) {
                n = 0;
                //n = noise(x, y);
                //n = (n + 1.0)*.5;
            }
            else {
                // typical noise
                n = noise(x, y); // (-1,1)
                n = (n + 1.0)*.5; // bias and scale to (0,1)
                //n = 128 + 128 * n; // not wrong though. :)
            }

            // wood noise
            //n = 20 * noise(x, y);
            //n = n - floor(n);

            // Map the values to the [0, 255] interval
            // color value has to be int!
            float color = floor(n * 255); // have to be int!
            //color = int(n); // this works the same as floor!
            outfile << color << " ";
        }
        outfile << "\n";
    }
    return 0;
}
