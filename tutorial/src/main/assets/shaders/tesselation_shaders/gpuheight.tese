#version 320 es
layout (quads, fractional_odd_spacing, ccw) in;

uniform sampler2D heightMap;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec2 TextureCoord[];

out float Height;

void main()
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec2 t0 = mix(TextureCoord[0], TextureCoord[1], u);
    vec2 t1 = mix(TextureCoord[3], TextureCoord[2], u);
    vec2 texCoord = mix(t0, t1, v);

    Height = texture(heightMap, texCoord).y * 10.0 - 2.0;

    vec4 p0 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, u);
    vec4 p1 = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, u);
    vec4 p = mix(p0, p1, v);

    vec4 uVec = gl_in[1].gl_Position - gl_in[0].gl_Position;
    vec4 vVec = gl_in[3].gl_Position - gl_in[0].gl_Position;
    vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0.));

    gl_Position = projection * view * model * (p + normal * Height);
}
