#version 330 core
layout (location = 0) in vec3 aPos;
uniform float u_time;
void main() {
gl_Position = vec4(aPos, 1.0f);
}