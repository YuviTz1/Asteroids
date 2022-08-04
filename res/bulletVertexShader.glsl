#version 330 core
layout(location = 1) in vec3 aPos;

uniform mat4 transform;

void main() {
    gl_Position = transform*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}