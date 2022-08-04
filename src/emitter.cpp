#include "emitter.hpp"

emitter::emitter()
	: particleShader("../../res/particleVertexShader.shader", "../../res/particleFragmentShader.shader"), particleVec(50000)
{
	float quadVertices[] = {
		// positions
		-0.02f, 0.02f, 0.0f,
		0.02f, -0.02f, 0.0f,
		-0.02f, -0.02f, 0.0f,
		-0.02f, 0.02f, 0.0f,
		0.02f, -0.02f, 0.0f,
		0.02f, 0.02f, 0.0f};

	// setup OpenGL buffers
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// set up instanced buffer with particle positions
	glGenBuffers(1, &instancedTranslationVBO); // buffer containing translation data
	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle) * numParticles, particleVec.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(particle), (void *)0);
	glVertexAttribDivisor(1, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	previousTime = glfwGetTime();
	scaleMat = glm::scale(scaleMat, glm::vec3(1.0f, 1.0f, 1.0f));
}

void emitter::update()
{
	for (int i = 0; i < numParticles; i++)
	{
		if (particleVec[i].lifetime > 0)
		{
			// update position and lifetime
			particleVec[i].position += particleVec[i].force;
			particleVec[i].lifetime -= (glfwGetTime() - previousTime);
		}
		else
		{
			// draw offscreen
			particleVec[i].position = glm::vec3(-100);
			particleVec[i].lifetime = random_number_between(1.0f, 6.0f);
		}
	}

	previousTime = glfwGetTime();
	scaleMat = glm::scale(glm::mat4(1.0f), scaleVec);
}

void emitter::draw()
{
	particleShader.use();

	// set scale matrix uniform
	unsigned int scaleMatLoc = glGetUniformLocation(particleShader.ID, "scaleMat");
	glUniformMatrix4fv(scaleMatLoc, 1, GL_FALSE, glm::value_ptr(scaleMat));

	// set color uniform
	unsigned int colorVecLoc = glGetUniformLocation(particleShader.ID, "fColor");
	glUniform3f(colorVecLoc, particleColor[0], particleColor[1], particleColor[2]);

	glBindBuffer(GL_ARRAY_BUFFER, instancedTranslationVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle) * numParticles, particleVec.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numParticles);
}

void emitter::emit(glm::vec3 x, glm::vec3 a)
{
	for (int i = 0; i < numParticles; i++)
	{
		// for particles with lifetime <= 0, spawn them at position of player
		if (particleVec[i].lifetime <= 0)
		{
			particleVec[i].position = x;
			particleVec[i].lifetime = random_number_between(1.0f, 6.0f);

			// add force opposite to direction of player acceleration
			particleVec[i].force = -a / 150.0f;

			// add random spread
			particleVec[i].force.x += particleVec[i].force.x * random_number_between(0.25, 1.0f);
			particleVec[i].force.y += particleVec[i].force.y * random_number_between(0.25, 1.0f);
		}
	}
}