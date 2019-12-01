#version 150
// #version 330 core
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

attribute vec3 position;//aPos
attribute vec2 texcoord;//aTexCoords;
attribute vec3 normal;//aNormal;

varying vec3 v_position;
varying vec2 v_texcoord;//TexCoords
varying vec3 v_normal;
// varying vec3 PositionCS;

void main()
{
    v_texcoord = texcoord;
    // v_position = position; 
    v_position = vec3(model * vec4(position, 1.0));
    // PositionCS = vec3(view * vec4(WorldPos, 1.0));
    // v_normal = normal;
    v_normal = mat3(model) * normal;   

    gl_Position =  <transform>; // projection * view * vec4(WorldPos, 1.0);
    // gl_Position =  projection * view * vec4(position, 1.0);
}