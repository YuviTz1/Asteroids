#include "asteroid.hpp"

asteroid::asteroid()
    : asteroidShader("../../res/asteroidVertexShader.glsl", "../../res/asteroidFragmentShader.glsl")
{

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // generate random x and y coordinates for spawning the asteroid
    x.x = (glm::length(v) <= 0.00525) ? random_number_between(0.7f, 1.6f) : random_number_between(-0.7f, -1.6f);
    x.y = (glm::length(v) <= 0.00525) ? random_number_between(0.7f, 1.6f) : random_number_between(-0.7f, -1.6f);

    scaleMat = glm::scale(scaleMat, glm::vec3(scale));

    // radius of asteroid according to its scale
    radius = 0.016f * glm::length(glm::vec3(scale)) * glm::length(glm::vec3(0.5f));
}

void asteroid::draw()
{
    glBindVertexArray(VAO);
    asteroidShader.use();                           // use shader
    asteroidShader.setMat4("transform", transform); // set transformation matrix
    asteroidShader.setMat4("scaleMat", scaleMat);   // set scale matrix
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void asteroid::update()
{
    x = x + v;

    // wrap around the screen
    if (x.x > 2 || x.x < -2)
    {
        x.x = -x.x;
    }
    if (x.y > 2 || x.y < -2)
    {
        x.y = -x.y;
    }

    transform = glm::mat4(1.0f);
    // translate and scale the transformation matrix
    transform = glm::scale(transform, glm::vec3(0.5f));
    transform = glm::translate(transform, glm::vec3(x));
}