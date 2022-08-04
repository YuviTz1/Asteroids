#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_class.hpp"
#include "utility.hpp"

class asteroid
{
private:
    float vertices[21] = {
        0.0f, 0.0f, 0.0f,
        0.10f, 0.08f, 0.0f,
        0.0f, 0.15f, 0.0f,
        -0.10f, 0.08f, 0.0f,
        -0.10f, -0.08f, 0.0f,
        0.0f, -0.15f, 0.0f,
        0.10f, -0.08f, 0.0f};

    unsigned int indices[18] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1};

    unsigned int EBO; // element buffer object
    unsigned int VAO; // vertex array object
    unsigned int VBO; // vertex buffer object

    Shader asteroidShader;

    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 scaleMat = glm::mat4(1.0f);

    // initialize with random velocity
    glm::vec3 v = glm::vec3(random_number_between(-0.010f, 0.010f), random_number_between(-0.010f, 0.010f), 0.0f);

public:
    float scale = random_number_between(0.7f, 1.5f); // random scale
    glm::vec3 x = glm::vec3(0.0f);                   // position vector
    float radius;
    bool destroy = false;   

    asteroid();
    void draw();
    void update();
};