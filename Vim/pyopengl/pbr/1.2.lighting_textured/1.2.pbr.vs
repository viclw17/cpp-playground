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

void main()
{
    v_texcoord = texcoord;

    v_position = position; // transform done in fs
    // v_position = vec3(model * vec4(position, 1.0));

    // local normal
    v_normal = normal; // transform done in fs
    // transform normal to world space
    // v_normal = mat3(model) * normal; 

    gl_Position = <transform>; // transform done in fs
    // gl_Position =  projection * view * vec4(v_position, 1.0);
}