
uniform vec3 iResolution;// viewport resolution (in pixels)
uniform float iTime;// shader playback time (in seconds)
uniform float iTimeDelta;// render time (in seconds)
uniform int iFrame;// shader playback frame
uniform float iChannelTime[4];// channel playback time (in seconds)
uniform vec3 iChannelResolution[4];// channel resolution (in pixels)
uniform vec4 iMouse;// mouse pixel coords. xy: current (if MLB down), zw: click
uniform samplerXX iChannel0..3;// input channel. XX = 2D/Cube
uniform vec4 iDate;// (year, month, day, time in seconds)
uniform float iSampleRate;// sound sample rate (i.e., 44100)



/* Bare bones of a monte-carlo ray tracer
At each bounce look up BRDF and accumulate as a multiply-add to incident light, so
we never need to store all bounces.
Bounce directions are random on a hemisphere - would be faster if biases are added but
want a minimal-complexity implementation
*/
// https://www.shadertoy.com/view/llXfR8
//--------scene--------

float SDF(vec3 pos)
{
    return min(min(min(
                length(pos)-1.,// sphere in the centre
                length(pos-vec3(0,-11,0))-10.),// sphere below
                length(pos-vec3(-6,0,0))-5.),// sphere to the left
                10.-length(pos)// inverse sphere containing the scene
            );
}

void BRDF(out vec3 tint,out vec3 emissive,in vec3 pos,in vec3 toEye,in vec3 toLight,in vec3 normal)
{
    tint=vec3(.95);// default everything to white paint
    if(length(pos-vec3(-6,0,0))-5.<=.004)// are we on the left sphere?
    {
        tint=vec3(.95,0,0);// paint it red
    }

    // lighting - just basic n.l
    tint*=dot(normal,toLight);// no need to do max(0,) because we never fire rays inside the surface

    // emit light from some surfaces
    emissive=vec3(0);// default: non-emissive

    if(length(pos)>9.)// are we on the outer sphere?
    {
        // draw an emissive-only background
        tint=vec3(0);
        emissive=vec3(10)*pow(max(0.,dot(normalize(pos),normalize(vec3(2,3,1)))),10.)
        +.7;
    }
}

//--------renderer-------

// From https://www.shadertoy.com/view/ltXBz8
vec3 SphereRand(uint seed)
{
    float a=(float((seed*0x73493U)&0xfffffU)/float(0x100000))*2.-1.;
    float b=6.283*(float((seed*0xAF71fU)&0xfffffU)/float(0x100000));
    float cosa=sqrt(1.-a*a);
    return vec3(cosa*cos(b),a,cosa*sin(b));
}

vec3 HemisphereRand(vec3 a,uint seed)
{
    vec3 r=SphereRand(seed);
    return dot(r,a)>.0?r:-r;
}

vec3 GetNormal(vec3 pos)
{
    vec2 d=vec2(-1,1)*.01;
    return normalize(
        SDF(pos+d.xxx)*d.xxx+
        SDF(pos+d.yyx)*d.yyx+
        SDF(pos+d.yxy)*d.yxy+
        SDF(pos+d.xyy)*d.xyy
    );
}

vec3 Trace(vec3 pos,vec3 ray)
{
    float e=.001;
    pos+=ray*e*4.;// try to prevent false self-intersect
    for(int i=0;i<200;i++)
    {
        float s=SDF(pos);
        pos+=s*ray;
        if(s<e)break;
    }
    return pos;
}

void mainImage(out vec4 fragColor,in vec2 fragCoord)
{
// random seed per-pixel
// for best results this should be random noise, but I like having an obvious pattern
// so I can see when the render has converged
// also looks cool if you set it to 0
uint pixelSeed=uint(fragCoord.x)^uint(fragCoord.y);

// anti-aliasing
vec2 jitter=vec2((pixelSeed^uint(iFrame*7))&0xffU,((pixelSeed^uint(iFrame*29))/5U)&0xffU)/float(0x100U)-.5;

// camera setup
vec3 ray=normalize(vec3(
        (fragCoord.xy+jitter-iResolution.xy*.5)/iResolution.y,
        1.
    ));
    vec3 pos=vec3(0,0,-3);
    
    // monte-carlo loop
    vec3 emit=vec3(0);
    vec3 tint=vec3(1);
    const uint bounces=8U;
    for(uint i=0U;i<bounces;i++)
    {
        pos=Trace(pos,ray);
        vec3 normal=GetNormal(pos);
        
        // fire the next ray
        uint seed=pixelSeed^(uint(iFrame)/(1u+i));// bounce directions should be independent of each other
        vec3 newRay=HemisphereRand(normal,seed);
        vec3 tinti,emiti;
        
        // sample what colour the next ray should be tinted, and any emissive effects
        BRDF(tinti,emiti,pos,-ray,newRay,normal);
        
        // apply previous accumulated tint to emissive colour from this point
        emit+=tint*emiti;
        
        // accumulate tint
        tint*=tinti;
        
        if(length(tint)==0.)break;// optimisation - ignore bounces from a surface that doesn't bounce any light
        
        ray=newRay;
    }
    
    // sum colour with previous sample, keep count of total in alpha
    fragColor.rgb=emit;
    fragColor.a=1.;
    
    if(iFrame>0)
    {
        fragColor+=texelFetch(iChannel0,ivec2(fragCoord.xy),0);
    }
}
