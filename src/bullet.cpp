#include "bullet.hpp"

bullet::bullet(playerSpaceship player)
    : bulletShader("../../res/bulletVertexShader.glsl", "../../res/bulletFragmentShader.glsl")
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(1);

    glPointSize(5.0f);

    //  initialize velocity and position
    v = v + glm::vec3(moveSpeed * sin(player.rotAngle), moveSpeed * cos(player.rotAngle), 0.0f);
    x = x + player.x;
}

void bullet::draw()
{
    glBindVertexArray(VAO);
    bulletShader.use();                       // use shader
    bulletShader.setMat4("transform", trans); // set transformation matrix
    glDrawArrays(GL_POINTS, 0, 1);
}

void bullet::update()
{
    x = x + v * h; // update position

    trans = glm::mat4(1.0f);

    // translate and scale the transformation matrix
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    trans = glm::translate(trans, x);
}