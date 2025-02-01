#version 330 core
in vec3 color;
out vec4 FragColor;
void main() {
    // FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    FragColor = vec4(color, 1.0f);
}