cmake_minimum_required(VERSION 3.9.1)
project(Asteroids)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} playerSpaceship.cpp shader_class.cpp bullet.cpp gameManager.cpp asteroid.cpp emitter.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} GLEW GL glfw)
