#version 330 core
layout(location = 2) in vec3 aPos;

uniform mat4 transform;
uniform mat4 scaleMat;

void main() {
    gl_Position = transform*(scaleMat*vec4(aPos.x, aPos.y, aPos.z, 1.0));
}