#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture0;
uniform sampler2D screenTexture1;
uniform sampler2D screenTexture2;

void main()
{
    vec3 col[3];
    col[0] = texture(screenTexture0, TexCoords).rgb;
    col[1] = texture(screenTexture1, TexCoords).rgb;
    col[2] = texture(screenTexture2, TexCoords).rgb;
    int frac = int(gl_FragCoord.y);
    frac = frac / 100;
    frac = frac % 3;
    FragColor = vec4(col[frac], 1.0);
}