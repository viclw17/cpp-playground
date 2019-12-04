#version 330 core
// out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 normal;

uniform int p;
uniform int t;

varying vec3 v_position; // WorldPos;
varying vec2 v_texcoord; // TexCoords;
varying vec3 v_normal;

// material parameters
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
// lights
uniform vec3 lightPositions[1];
uniform vec3 lightColors;
// camera
uniform vec3 camPos;

uniform float time;
const float PI = 3.14159265359;

vec3 lightPosition = vec3(10*sin(time),5,10*cos(time));

// ----------------------------------------------------------------------------

vec3 localPos = v_position;
vec3 ViewPos = vec3(view * model * vec4(v_position, 1));
vec3 WorldPos = vec3(model * vec4(v_position, 1));

vec3 localNormal = v_normal;
vec3 worldNormal = vec3(model * vec4(v_normal, 1));
// vec3 Normal = normalize(normal * vec4(v_normal,1.0)).xyz; // glumpy
vec3 Normal = worldNormal;

vec2 TexCoords = v_texcoord;

// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture2D(normalMap, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------
void main()
{            
    #if 0
    vec3 albedo     = vec3(.2);
    float metallic  = 0;
    float roughness = .5;
    #else
    vec3 albedo     = pow(texture2D(albedoMap, TexCoords).rgb, vec3(2.2)); //2.2
    float metallic  = texture2D(metallicMap, TexCoords).r;
    float roughness = texture2D(roughnessMap, TexCoords).r;
    float ao        = texture2D(aoMap, TexCoords).r;
    #endif

    vec3 N = worldNormal; 
    // vec3 N = getNormalFromMap();
    vec3 V = normalize(camPos - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    // for(int i = 0; i < 4; ++i) 
    // {
        // calculate per-light radiance
        vec3 L = normalize(lightPosition - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPosition - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
        vec3 nominator    = NDF * G * F; 
        float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 specular = nominator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;  
        // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    
    // }   
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo * ao; //0.03
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 
    vec3 final = color;
    
    // tex
    if(t == 0)
        color = albedo;
    else if (t == 1)    
        color = (N+1)*.5;
    else if (t == 2)
        color = vec3(metallic);
    else if (t == 3)
        color = vec3(roughness);
    else
        color = final;

    // BRDF specular term
    // color = vec3(DistributionGGX(N, H, roughness)); // D
    // color = vec3(GeometrySmith(N, V, L, roughness)); // G
    // color = fresnelSchlick(max(dot(H, V), 0.0), F0);
    // color = fresnelSchlick(max(dot(H, V), 0.0), vec3(.1));// F
    // color = fresnelSchlick(max(dot(N, V), 0.0), vec3(.1));// F
    // if (dot(N, V)<.1)
    //     color = vec3(1,0,0);
    // else if (dot(N, V)>.5)
    //     color = vec3(0,1,0);
    // else
    //     color = vec3(1,1,0);

    // if (dot(H, V)<.3)
    //     color = vec3(1,0,0);// * NDF*G;
    // else if (dot(H, V)>.5)
    //     color = vec3(0,1,0);// * NDF*G;
    // else
    //     color = vec3(1,1,0);// * NDF*G;

    // float ior = 1.5;
    // float f0 = abs ((1.0 - ior) / (1.0 + ior));
    // f0 = f0 * f0;
    // color = vec3(f0 + (1-f0) * pow( 1 - dot(H, V), 5));


    // color = specular;
    // color = Lo;

    // n
    // color = v_normal; // local normal
    // color = Normal; // ws
    // color = (N+1)*.5; // nmap

    // p
    if(p==0){
        vec3 lp = v_position;
        color = lp;
        // color = vec3(pow(abs(floor(lp.z*10)/10),.5));
    }else if(p==1){
        vec3 wp = vec3(model*vec4(v_position, 1));
        color = wp;
        // color = vec3(pow(abs(floor(wp.z*10)/10),.5));
    }else if(p==2){
        vec3 vp = vec3(view * model * vec4(v_position, 1));
        color = vp;
        // color = vec3(pow(abs(floor(vp.x*10)/10),.5));
    }else{
        color = final;
    }
    
    // uv
    // color = vec3(v_texcoord.x);// uv.x
    // color = vec3(v_texcoord.y);// uv.y
    // color = vec3((mod(v_texcoord.xy,0.1)*10),0); // uv mod
    // color = vec3(floor(v_texcoord.xy*10)/10,0); // uv floor
    
    // color = vec3(.5);
    gl_FragColor = vec4(color, 1.0);
}
