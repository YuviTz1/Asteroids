#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "gameManager.hpp"
#include "playerSpaceship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"

auto start = std::chrono::system_clock::now(); // timer

// handle window inputs
void processInput(GLFWwindow *window, playerSpaceship &player, gameManager &manager)
{
    float moveSpeed = 0.3f;            // player move speed
    float rotAngle = 0.0009f;          // player rotation speed
    player.updateAcc(glm::vec3(0.0f)); // update player acceleration with 0 if no key pressed

    // close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // accelerate spaceship
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // update acceleration with respect to its x and y components
        player.updateAcc(glm::vec3(moveSpeed * sin(player.rotAngle), moveSpeed * cos(player.rotAngle), 0.0f));
    }

    // rotate spaceship
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player.updateRot(-rotAngle);
    }

    // rotate spaceship
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        player.updateRot(rotAngle);
    }

    // fire bullet
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // check elapsed time in order to prevent firing every frame
        auto end = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (elapsed_time.count() >= 400) // fire after 400 milliseconds
        {
            start = std::chrono::system_clock::now();
            manager.addBullet(player);
        }
    }
}

int main(void)
{
    // glfw initialise
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 900, "Particles!!", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // check if GLEW is working fine
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW init error" << std::endl;
    }

    glViewport(0, 0, 1200, 900);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode

    gameManager manager;

    while (!glfwWindowShouldClose(window))
    {
        // clear screen with specified color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0782, 0.0782, 0.0782, 1);

        manager.checkBounds();
        manager.update();
        manager.checkCollision();

        /* handle inputs */
        processInput(window, manager.player, manager);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}