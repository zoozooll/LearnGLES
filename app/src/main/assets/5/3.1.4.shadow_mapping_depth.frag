#version 320 es
precision mediump float;

uniform vec3 lightPos;
//out vec4 fragColor;
in vec3 vPos_World;


void main()
{             
//    gl_FragDepth = 0.0;
//    fragColor = vec4(0.0);
    gl_FragDepth = distance(vPos_World, lightPos);
}