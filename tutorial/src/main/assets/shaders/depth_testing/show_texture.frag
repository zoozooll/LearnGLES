#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture0;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture0, TexCoord);
}
