#version 320 es

precision mediump float;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
//	FragColor = vec4(dFdx(FragColor).r * 1000.);
}