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
const unsigned int WIDTH  = 600;
const unsigned int HEIGHT = 600;

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

#define VEND 0.05f
#define TSRT 1.0f - VEND

// vertices
float vertices[] = {
     VEND,  VEND + TSRT, 0.0f,
     VEND, -VEND + TSRT, 0.0f,
    -VEND, -VEND + TSRT, 0.0f,
	 VEND,  VEND + TSRT, 0.0f,
	-VEND, -VEND + TSRT, 0.0f,
	-VEND,  VEND + TSRT, 0.0f,
};

#endif // MAIN_H
