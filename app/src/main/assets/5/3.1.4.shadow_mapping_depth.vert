#version 320 es
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;

uniform mat4 model;

out vec3 vPos_World;

void main()
{
    vec4 pos4_World = model * vec4(aPos, 1.0);
    vPos_World = pos4_World.xyz / pos4_World.w;
    gl_Position = lightSpaceMatrix * pos4_World;
}