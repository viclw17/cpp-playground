#version 150
// #version 330 core
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

attribute vec3 aPos;
attribute vec2 aTexCoords;
attribute vec3 aNormal;

varying vec2 TexCoords;
varying vec3 WorldPos;
varying vec3 Normal;
varying vec3 PositionCS;

void main()
{
    TexCoords = aTexCoords;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    PositionCS = vec3(view * vec4(WorldPos, 1.0));
    Normal = mat3(model) * aNormal;   
    // Normal = aNormal;

    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}