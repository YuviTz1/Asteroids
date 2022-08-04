#pragma once

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_class.hpp"
#include "utility.hpp"
#include "playerSpaceship.hpp"

class bullet
{
private:
  float vertices[3] = {0.0f, 0.0f, 0.0f};

  float moveSpeed = 3.0f;
  float h = 0.01667; // timestep for 60 fps

  unsigned int VAO; // vertex array object
  unsigned int VBO; // vertex buffer object

  Shader bulletShader;
  glm::vec3 v = glm::vec3(0.0f);     // velocity vector
  glm::mat4 trans = glm::mat4(1.0f); // transformation matrix

public:
  bullet(playerSpaceship player);
  void draw();
  void update();

  glm::vec3 x = glm::vec3(0.0f); // position vector
};