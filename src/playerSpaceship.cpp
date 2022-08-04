#include "playerSpaceship.hpp"

playerSpaceship::playerSpaceship()
    : spaceshipShader("../../res/playerSpaceshipVertexShader.glsl", "../../res/playerSpaceshipFragmentShader.glsl")
{
    glGenVertexArrays(1, &VAO);                                                //
    glBindVertexArray(VAO);                                                    //
                                                                               //
    glGenBuffers(1, &VBO);                                                     //
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        //
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Set up OpenGL buffers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),         //
                          (void *)0);                                          //
    glEnableVertexAttribArray(0);                                              //
                                                                               //
    trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
}

void playerSpaceship::draw()
{
    // bind buffers, use shaders and draw
    glBindVertexArray(VAO);
    spaceshipShader.use();                       // use shader
    spaceshipShader.setMat4("transform", trans); // set transformation matrix
    glDrawArrays(GL_TRIANGLES, 0, 3);

    particleEmitter.draw();
}

void playerSpaceship::updateAcc(glm::vec3 acc)
{
    a = acc;
    if (glm::length(acc) > 0) // if accelerating, emit particles
    {
        particleEmitter.emit(x, a);
    }
}

void playerSpaceship::update()
{
    v = v + a * h; // update position and acceleration
    x = x + v * h; // according to euler integration

    // wrap around the screen
    if (x.x >= 2 || x.x <= -2)
    {
        x.x = -x.x;
    }
    if (x.y >= 2 || x.y <= -2)
    {
        x.y = -x.y;
    }

    rotAngle += rotAngleInc;

    trans = glm::mat4(1.0f);

    // scale, translate, rotate the transformation matrix
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    trans = glm::translate(trans, x);
    trans = glm::rotate(trans, -rotAngle, glm::vec3(0.0f, 0.0, 1.0f));

    particleEmitter.update();
}

void playerSpaceship::updateRot(float angle)
{
    rotAngleInc += angle;
    rotAngleInc = max(-0.040f, min(0.040f, rotAngleInc)); // clamp angle increment
}

void playerSpaceship::reset()
{
    v = glm::vec3(0.0f);
    a = glm::vec3(0.0f);
    x = glm::vec3(0.0f);

    rotAngleInc = 0.0f;
    rotAngle = 0.0f;
}