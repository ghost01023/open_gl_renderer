#version 330 core
out vec4 FragColor;
uniform float u_time;
void main() {
    float intensity_blue = 0.5 * sin(u_time);
    float intensity_green = sin(u_time);
    FragColor = vec4(intensity_blue / intensity_green, intensity_green, intensity_blue, intensity_green/intensity_blue);
}