#ifndef MAIN_H
#define MAIN_H

// c headers
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// opengl headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// my files
#include "utility.h"

// window dimensions
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// shader sources
const char *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\n gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
const char *fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n FragColor = vec4(0.9f, 0.9f, 0.0f, 1.0f);\n}\n\0";

// background color
float bg_rgb[] = { 0.2f, 0.3f, 1.0f, 1.0f };

// array & buffer objects
unsigned int VBO, VAO;

// functions
void initializeGLFW();
GLFWwindow* buildWindow();
unsigned int buildShaders();
void display(GLFWwindow* window, unsigned int shaderProgram);
void keyboard(GLFWwindow *window);
void resize_window(GLFWwindow* window, int width, int height);
void ComputePositionOffsets(float *fOffsets); // fOffsets[0] = x offset, fOffsets[1] = y offset
void AdjustVertexData(float *fOffsets);

// vertices
float vertices[] = {
     0.25f,  0.25f, 0.0f,
     0.25f, -0.25f, 0.0f,
    -0.25f, -0.25f, 0.0f,
};

#endif // MAIN_H
