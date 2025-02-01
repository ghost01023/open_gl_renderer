#version 330 core
in vec3 color;
out vec4 FragColor;
// uniform float u_time;
void main() {
    // float intensity_blue = 0.5 * sin(u_time);
    // float intensity_green = sin(u_time);
    // FragColor = vec4(0.4f, 0.1f, 0.9f, 1.0f);
    FragColor = vec4(color, 1.0f);
}