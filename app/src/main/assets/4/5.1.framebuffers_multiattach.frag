#version 320 es
precision lowp float;

layout(location = 0) out vec4 FragColor0; // Output for the first color attachment
layout(location = 1) out vec4 FragColor1; // Output for the second color attachment
layout(location = 2) out vec4 FragColor2; // Output for the third color attachment

void main() {
    FragColor0 = vec4(1.0, 0.0, 0.0, 1.0); // Red for the first attachment
    FragColor1 = vec4(0.0, 1.0, 0.0, 1.0); // Green for the second attachment
    FragColor2 = vec4(0.0, 0.0, 1.0, 1.0); // Blue for the third attachment
}