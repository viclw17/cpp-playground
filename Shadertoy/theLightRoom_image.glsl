// License: Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// Copyright © 2019 Stefan Schmidt
//
// Basic path tracing implementation for learning.
// BRDFs: Lambert/Blinn-Phong/reflection/refraction/Lommel/GGX
//
// Based on https://www.shadertoy.com/view/XdcfRr
// ---------------------------------------------------------------------

// Things to try (in Buffer A):
//
// * Play with scene and materials (also, check the importance sampling demo
//     at: http://www.shadertoy.com/view/3lB3DR)
// * Play with NUM_SAMPLES and NUM_DEPTH
// * Play with SOLO_DEPTH to see the effects of a ray depth on the final image
// * Play with SHADOW_EPSILON to adjust Shadow Acne and Peter Panning
// * Disable SSAA to see its effects
// * Play with FOCAL_LENGTH
// ---------------------------------------------------------------------

// Shader entry point
void mainImage(out vec4 fragColor,vec2 fragCoord){
    vec2 uv=fragCoord.xy/iResolution.xy;
    vec3 col=vec3(0.);
    
    // Read texture in Buffer A
    col=texture(iChannel0,uv).rgb;
    
    // Inverse gamma function
    col=pow(col,vec3(1./2.2));
    
    // Post-processing: color grading
    col=pow(col,vec3(.8,.85,.9));
    
    // Post-processing: vignette
    col*=.5+.5*pow(16.*uv.x*uv.y*
        (1.-uv.x)*(1.-uv.y),.2);
        
        // Return fragment color
        fragColor=vec4(col,1.);
}
    