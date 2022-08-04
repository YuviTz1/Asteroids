#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader_class.hpp"
#include "utility.hpp"
#include "particle.hpp"

class emitter
{
public:
	int numParticles = 2000;
	// float dt = 0.0001;			  // fall down speed
	float previousTime = 0; // previous frame time used for updating lifetimes
	// float forceMultiplier = 1.0f; // for updating force via GUI

	// vector of patricles
	std::vector<particle> particleVec;
	
	// scale matrix
	glm::vec3 scaleVec = glm::vec3(0.1f);
	glm::mat4 scaleMat = glm::mat4(1.0f);
	float particleColor[3] = {1.0f, 1.0f, 1.0f};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int instancedTranslationVBO;

	Shader particleShader;

	emitter();

	void update();
	void draw();
	void emit(glm::vec3 x, glm::vec3 a);
};