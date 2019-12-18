void mainImage(out vec4 fragColor,in vec2 fragCoord)
{
    fragColor=texelFetch(iChannel0,ivec2(fragCoord.xy),0);
    fragColor.rgb/=fragColor.a;

    //    fragColor.rgb = pow(fragColor.rgb,vec3(1./2.2));
    // actual sRGB - slightly darkens shadows
    fragColor.rgb=mix(
        12.92*fragColor.rgb,
        1.055*pow(fragColor.rgb,vec3(1./2.4)),
        step(.0031308,fragColor.rgb))
        -.055;
        
        fragColor.a=1.;
}
    