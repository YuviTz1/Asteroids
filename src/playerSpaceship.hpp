#pragma once

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_class.hpp"
#include "utility.hpp"
#include "emitter.hpp"

class playerSpaceship
{
private:
    float vertices[9] = { // vertices for players model
        -0.05f, -0.09f, 0.0f,
        0.05f, -0.09f, 0.0f,
        0.0f, 0.05f, 0.0f};

    unsigned int VAO; // vertex array object
    unsigned int VBO; // vertex buffer object

    Shader spaceshipShader;

    glm::mat4 trans; // transformation matrix

    glm::vec3 v = glm::vec3(0); // velocity vector
    float h = 0.01667;          // delta time for 60fps

    emitter particleEmitter;

public:
    glm::vec3 a = glm::vec3(0); // acceleration vector
    glm::vec3 x = glm::vec3(0); // position vector
    float rotAngleInc = 0;      // angle increment
    float rotAngle = 0.0f;      // players angle with respect to y-axis

    playerSpaceship();
    void draw();
    void updateAcc(glm::vec3 acc);
    void updateRot(float angle);
    void update();
    void reset();
};