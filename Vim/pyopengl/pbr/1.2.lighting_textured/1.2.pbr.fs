#version 330 core
// out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 normal; // glumpy normal matrix

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
uniform vec3 lightPositions;
uniform vec3 lightColors;

// camera
uniform vec3 camPos;

const float PI = 3.14159265359;

// Calculate the location of this fragment (pixel) in world coordinates
// vec3 WorldPos = v_position;
vec3 WorldPos = vec3(view * model * vec4(v_position, 1));
// Calculate normal in world coordinates
// vec3 Normal = v_normal;
vec3 Normal = normalize(normal * vec4(v_normal,1.0)).xyz;
vec2 TexCoords = v_texcoord;
vec3 PositionVS = vec3(view * vec4(v_position, 1));
// https://stackoverflow.com/questions/14980712/how-to-get-flat-normals-on-a-cube
// vec3 Normal = normalize(cross(dFdx(PositionCS), dFdy(PositionCS)));


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
    vec3 albedo     = pow(texture2D(albedoMap, TexCoords).rgb, vec3(2.2)); //2.2
    float metallic  = texture2D(metallicMap, TexCoords).r;
    float roughness = texture2D(roughnessMap, TexCoords).r;
    float ao        = texture2D(aoMap, TexCoords).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(camPos - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    // for(int i = 0; i < 1; ++i) 
    // {
        // calculate per-light radiance
        vec3 L = normalize(lightPositions - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions - WorldPos);
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

        vec3 diffuse = (kD * albedo / PI);
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

    
    // tex
    // color = albedo;
    // color = N;
    // color = vec3(metallic);
    // color = vec3(roughness);

    // BRDF specular term
    // color = vec3(DistributionGGX(N, H, roughness)); // D
    // color = vec3(GeometrySmith(N, V, L, roughness)); //G
    // color = fresnelSchlick(max(dot(H, V), 0.0), vec3(0.02)); // F

    // color = diffuse;
    // color = specular;

    // color = Lo;

    // n
    // color = Normal;
    // color = vec3(abs(Normal.x)); // test ws normal
    // color = N;

    // wp
    // color = v_position;
    // color = vec3(v_position.x);
    // color = vec3(v_position.y);
    // color = vec3(v_position.z);

    // view space
    // color = PositionVS;

    // uv
    // color = vec3(v_texcoord.x);// uv.x
    // color = vec3(v_texcoord.y);// uv.y
    // color = vec3((mod(v_texcoord.xy,0.1)*10),0); // uv mod
    // color = vec3(floor(v_texcoord.xy*10)/10,0); // uv floor
    // color = vec3(1);
    gl_FragColor = vec4(color, 1.0);
}
