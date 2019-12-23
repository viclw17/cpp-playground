// https://www.shadertoy.com/view/WllGWn


// License: Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// Copyright © 2019 Stefan Schmidt
//
// Basic path tracing implementation for learning.
// BRDFs: Lambert/Blinn-Phong/reflection/refraction/Lommel/GGX
//
// Based on https://www.shadertoy.com/view/XdcfRr
// ---------------------------------------------------------------------

// Parameters
#define NUM_SAMPLES 10// Number of samples per pixel
#define MAX_DEPTH 10// Max ray depth
// #define SOLO_DEPTH      0               // Shows only light of depth X
#define SHADOW_EPSILON .015
#define SSAA// Supersampling anti-aliasing
#define FOCAL_LENGTH .019// Camera focal length
#define FRAME_WIDTH .036// Camera sensor width

// Constants
#define M_PI radians(180.)
#define FAR_PLANE 1e3

// Materials
#define MAT_LAMBERT 0
#define MAT_BLINNPHONG 1
#define MAT_SPECULAR 2
#define MAT_REFRACTION 3
#define MAT_LOMMEL 4
#define MAT_GGX 5

struct Material{
    int type;
    
    vec3 albedo;// Albedo color
    vec3 specular;// Specular color
    float roughness;// Roughness or Phong exponent
    
    float ior;// Index of refraction
    
    vec3 emissive;// Emissive color
};

#define MAT_TOPLAMP 0
#define MAT_BLACKHOLE 1
#define MAT_GRAY 2
#define MAT_RED 3
#define MAT_BLUE 4
#define MAT_GRAY_BP 5
#define MAT_METAL 6
#define MAT_WATER 7
#define MAT_GLASS 8
#define MAT_DIAMOND 9
#define MAT_MOONDUST 10
#define MAT_WARMLIGHT 11
#define MAT_COLDLIGHT 12
#define MAT_COPPER 13
#define MAT_SILVER 14
#define MAT_GOLD 15
#define MAT_PLASTIC 16
#define MAT_CERAMIC 17
#define MAT_NUM 18

Material materials[MAT_NUM];

void initMaterials(){
    materials[MAT_TOPLAMP]=Material(MAT_LAMBERT,vec3(0.),
    vec3(.04),.3,1.,vec3(24.));
    materials[MAT_BLACKHOLE]=Material(MAT_LAMBERT,vec3(0.),
    vec3(.04),.3,1.,vec3(0.));
    materials[MAT_GRAY]=Material(MAT_LAMBERT,vec3(.75),
    vec3(.04),.3,1.,vec3(0.));
    materials[MAT_RED]=Material(MAT_LAMBERT,vec3(.75,.25,.25),
    vec3(.04),.3,1.,vec3(0.));
    materials[MAT_BLUE]=Material(MAT_LAMBERT,vec3(.25,.25,.75),
    vec3(.04),.3,1.,vec3(0.));
    materials[MAT_GRAY_BP]=Material(MAT_BLINNPHONG,vec3(.75),
    vec3(.75),20.,1.,vec3(0.));
    materials[MAT_METAL]=Material(MAT_SPECULAR,vec3(0.),
    vec3(.65,.75,.72),.5,1.,vec3(0.));
    materials[MAT_WATER]=Material(MAT_REFRACTION,vec3(.95,.96,.98),
    vec3(.04),.3,1.3,vec3(0.));
    materials[MAT_GLASS]=Material(MAT_REFRACTION,vec3(.7,.98,.9),
    vec3(.04),.3,1.5,vec3(0.));
    materials[MAT_DIAMOND]=Material(MAT_REFRACTION,vec3(.92,.94,.75),
    vec3(.04),.3,2.2,vec3(0.));
    materials[MAT_MOONDUST]=Material(MAT_LOMMEL,vec3(.75),
    vec3(.04),.3,1.,vec3(0.));
    materials[MAT_WARMLIGHT]=Material(MAT_LOMMEL,vec3(.05),
    vec3(.04),.3,1.,2.*vec3(1.,.65,.4));
    materials[MAT_COLDLIGHT]=Material(MAT_LOMMEL,vec3(.05),
    vec3(.04),.3,1.,2.*vec3(.59,.76,1.));
    materials[MAT_COPPER]=Material(MAT_GGX,vec3(0.),
    vec3(.955,.637,.538),.4,1.,vec3(0.));
    materials[MAT_SILVER]=Material(MAT_GGX,vec3(0.),
    vec3(.972,.960,.915),.35,1.,vec3(0.));
    materials[MAT_GOLD]=Material(MAT_GGX,vec3(0.),
    vec3(1.,.766,.336),.3,1.,vec3(0.));
    materials[MAT_PLASTIC]=Material(MAT_GGX,vec3(.8,.06,.03),
    vec3(.04),.15,1.,vec3(0.));
    materials[MAT_CERAMIC]=Material(MAT_GGX,vec3(.8,.7,.65),
    vec3(.04),.3,1.,vec3(0.));
}

// Scene
struct Sphere{
    vec3 center;
    float radius;
};

struct Object{
    Sphere sphere;
    Material material;
};

#define NUM_OBJECTS 10
Object scene[NUM_OBJECTS];

void initScene(){
    // Feel free to change materials, positions and sizes...
    
    // Front and back walls
    scene[0]=Object(Sphere(vec3(0.,1.2,1e3+2.5),1e3),materials[MAT_GRAY]);
    scene[1]=Object(Sphere(vec3(0.,1.2,-1e3-2.5),1e3),materials[MAT_BLACKHOLE]);
    // Left and right walls
    scene[2]=Object(Sphere(vec3(-1e3-1.5,0.,0.),1e3),materials[MAT_RED]);
    scene[3]=Object(Sphere(vec3(1e3+1.5,0.,0.),1e3),materials[MAT_BLUE]);
    // Ceiling and floor
    scene[4]=Object(Sphere(vec3(0.,1e3+2.4,0.),1e3),materials[MAT_GRAY]);
    scene[5]=Object(Sphere(vec3(0.,-1e3,0.),1e3),materials[MAT_GRAY]);
    // Objects
    scene[6]=Object(Sphere(vec3(-.75,.51,1.3),.5),materials[MAT_METAL]);
    scene[7]=Object(Sphere(vec3(.75,.51,.3),.5),materials[MAT_GLASS]);
    // Top light and blocking sphere to avoid Peter Panning
    scene[8]=Object(Sphere(vec3(0.,20.+2.3925,0.),20.),materials[MAT_TOPLAMP]);
    scene[9]=Object(Sphere(vec3(0.,40.+2.4075,0.),40.),materials[MAT_BLACKHOLE]);
}

// Ray casting
struct Ray{
    vec3 origin;
    vec3 direction;
};

float castRayToSphere(Ray ray,Sphere sphere){
    vec3 oc=ray.origin-sphere.center;
    float qb=dot(ray.direction,oc);
    
    float det=qb*qb-dot(oc,oc)+sphere.radius*sphere.radius;
    if(det<0.)
    return FAR_PLANE;
    
    float sqrt_det=sqrt(det);
    
    float t1=-qb-sqrt_det;
    float t2=-qb+sqrt_det;
    
    if(t1<SHADOW_EPSILON)
    t1=FAR_PLANE;
    if(t2<SHADOW_EPSILON)
    t2=FAR_PLANE;
    
    return min(t1,t2);
}

bool castRay(Ray ray,out vec3 p,out vec3 normal,out Material material){
    float t=FAR_PLANE;
    
    for(int i=0;i<NUM_OBJECTS;++i){
        float t_=castRayToSphere(ray,scene[i].sphere);
        
        if(t_<t){
            t=t_;
            
            p=ray.origin+t*ray.direction;
            normal=normalize(p-scene[i].sphere.center);
            material=scene[i].material;
        }
    }
    
    return(t<FAR_PLANE);
}

// Random number generator
vec3 seed;

void initRandom(vec2 fragCoord){
    seed=vec3(fragCoord,iFrame);
}

float getRandom(){
    seed=fract(sin(cross(seed,vec3(12.9898,78.233,43.1931)))*43758.5453);
    
    return seed.x;
}

// Sampling
vec3 getHemisphereUniformSample(vec3 n){
    float cosTheta=getRandom();
    float sinTheta=sqrt(1.-cosTheta*cosTheta);
    
    float phi=2.*M_PI*getRandom();
    
    // Spherical to cartesian
    vec3 t=normalize(cross(n.yzx,n));
    vec3 b=cross(n,t);
    
    return(t*cos(phi)+b*sin(phi))*sinTheta+n*cosTheta;
}

// BRDF math
vec3 ggx(vec3 n,vec3 v,vec3 l,float roughness,vec3 F0){
    float alpha=roughness*roughness;
    float alpha2=alpha*alpha;
    
    float dotNL=clamp(dot(n,l),0.,1.);
    float dotNV=clamp(dot(n,v),0.,1.);
    
    vec3 h=normalize(v+l);
    float dotNH=clamp(dot(n,h),0.,1.);
    float dotLH=clamp(dot(l,h),0.,1.);
    
    // GGX microfacet distribution function
    float den=(alpha2-1.)*dotNH*dotNH+1.;
    float D=alpha2/(M_PI*den*den);
    
    // Fresnel with Schlick approximation
    vec3 F=F0+(1.-F0)*pow(1.-dotLH,5.);
    
    // Smith joint masking-shadowing function
    float k=.5*alpha;
    float G=1./((dotNL*(1.-k)+k)*(dotNV*(1.-k)+k));
    
    return D*F*G;
}

// Rendering
vec3 render(Ray ray){
    vec3 acc=vec3(0.);// Cumulative radiance
    vec3 att=vec3(1.);// Light attenuation
    
    for(int depth=0;depth<MAX_DEPTH;depth++){
        #ifdef SOLO_DEPTH
        if(depth==SOLO_DEPTH)
        acc=vec3(0);
        else if(depth==(SOLO_DEPTH+1))
        break;
        #endif
        vec3 p;
        vec3 normal;
        Material material;
        
        if(!castRay(ray,p,normal,material))
        break;
        
        // Orient normal towards ray direction
        float cosThetaI=dot(ray.direction,normal);
        
        vec3 facingNormal=(cosThetaI<0.)?normal:-normal;
        
        // Emissive radiance
        acc+=att*material.emissive;
        
        // Lambert material
        if(material.type==MAT_LAMBERT){
            vec3 reflected=getHemisphereUniformSample(facingNormal);
            
            att*=material.albedo*dot(facingNormal,reflected);
            
            ray=Ray(p,reflected);
        }
        // Blinn-Phong material
        else if(material.type==MAT_BLINNPHONG){
            vec3 reflected=getHemisphereUniformSample(facingNormal);
            
            vec3 h=normalize(-ray.direction+reflected);
            att*=material.albedo*dot(facingNormal,reflected)+
            material.specular*pow(max(dot(facingNormal,h),0.),material.roughness);
            
            ray=Ray(p,reflected);
        }
        // Specular material
        else if(material.type==MAT_SPECULAR){
            vec3 reflected=reflect(ray.direction,facingNormal);
            
            att*=material.specular;
            
            ray=Ray(p,reflected);
        }
        // Refraction material
        else if(material.type==MAT_REFRACTION){
            float eta=(cosThetaI<0.)?(1./material.ior):material.ior;
            
            vec3 refracted=refract(ray.direction,facingNormal,eta);
            
            if(all(equal(refracted,vec3(0.)))){
                // Total internal reflection
                vec3 reflected=reflect(ray.direction,facingNormal);
                
                ray=Ray(p,reflected);
            }else{
                // Fresnel F0
                float F0_=(material.ior-1.)/(1.+material.ior);
                float F0=F0_*F0_;
                
                // Fresnel with Schlick approximation
                float cosTheta=(cosThetaI<0.)?-cosThetaI:dot(refracted,normal);
                float F=F0+(1.-F0)*pow(1.-cosTheta,5.);
                
                if(getRandom()<F){
                    vec3 reflected=reflect(ray.direction,facingNormal);
                    
                    ray=Ray(p,reflected);
                }else{
                    att*=material.albedo;
                    
                    ray=Ray(p,refracted);
                }
            }
        }
        // Lommel-Seeliger material
        else if(material.type==MAT_LOMMEL){
            vec3 reflected=getHemisphereUniformSample(facingNormal);
            
            att*=material.albedo;
            
            ray=Ray(p,reflected);
        }
        // GGX material
        else{
            vec3 reflected=getHemisphereUniformSample(facingNormal);
            
            att*=dot(facingNormal,reflected)*(
                material.albedo+ggx(facingNormal,-ray.direction,reflected,
                material.roughness,material.specular));
                
            ray=Ray(p,reflected);
        }
    }
    
    return acc;
}
    
// Shader entry point
void mainImage(out vec4 fragColor,vec2 fragCoord){
    initRandom(fragCoord);
    initMaterials();
    initScene();
    
    // Camera
    vec2 mousePos=all(equal(iMouse.zw,vec2(0.)))?vec2(0.):
    clamp(2.*iMouse.xy/iResolution.xy-vec2(1.),vec2(-1.),vec2(1.));
    
    vec3 cameraPos=vec3(0.,1.2,-2.49)+vec3(mousePos,0.)*vec3(1.49,1.19,0.);
    vec3 cameraLookAt=vec3(0.,1.2,0.);
    
    vec3 cz=normalize(cameraLookAt-cameraPos);
    vec3 cx=normalize(cross(vec3(0.,1.,0.),cz));
    vec3 cy=cross(cz,cx);
    
    mat3 cameraTransform=mat3(cx,cy,cz);
    
    // Render frame
    vec3 col=vec3(0.);
    
    for(int i=0;i<NUM_SAMPLES;++i){
        #ifdef SSAA
        vec2 ssaa=vec2(getRandom(),getRandom());
        #else
        vec2 ssaa=vec2(.5);
        #endif
        vec2 screenCoord=vec2(2./iResolution.x)*(fragCoord+ssaa)-
        vec2(1.,iResolution.y/iResolution.x);
        
        vec3 projCoord=vec3(vec2(.5*FRAME_WIDTH)*screenCoord,FOCAL_LENGTH);
        
        vec3 rayDirection=cameraTransform*normalize(projCoord);
        
        Ray ray=Ray(cameraPos,rayDirection);
        col+=render(ray);
    }
    col/=vec3(NUM_SAMPLES);
    
    // Average with last frames
    if(all(equal(floor(fragCoord),vec2(0.)))){
        if(iMouse.z>0.)
        col=vec3(-iFrame);
        else
        col=texture(iChannel0,vec2(.5)/iResolution.xy).rgb;
    }else{
        if(iFrame>0){
            int frameStart=-int(texture(iChannel0,.5/iResolution.xy).x);
            vec3 colAvg=texture(iChannel0,fragCoord/iResolution.xy).rgb;
            col=mix(colAvg,col,1./float(iFrame+1-frameStart));
        }
    }
    
    fragColor=vec4(col,1.);
}
    