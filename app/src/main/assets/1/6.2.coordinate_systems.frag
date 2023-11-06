#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 screenSize;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(gl_FragCoord.zzz, 1.);
}