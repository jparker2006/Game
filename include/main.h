#ifndef MAIN_H
#define MAIN_H

// my files
#include "../include/utility.h"
#include "../include/matrix.h"
#include "../include/vector.h"

// window dimensions
const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

// shader program
unsigned int shaderProgram;

// background color
float bg_rgb[] = { 0.0f, 0.0f, 0.0f, 0.0f };

// vertex array & buffer objects
unsigned int VAO, VBO, IBO;

// perspective matrix
struct Matrix *cameraToClipMatrix;

// functions
void initializeGLFW();
GLFWwindow* buildWindow();
unsigned int buildShaders();
void display(GLFWwindow* window, unsigned int shaderProgram);
void keyboard(GLFWwindow *window);
void resize_window(GLFWwindow* window, int width, int height);

const int numberOfVertices = 8;

#define C_RED   1.0f, 0.0f, 0.0f, 1.0f
#define C_GREEN 0.0f, 1.0f, 0.0f, 1.0f
#define C_BLUE  0.0f, 0.0f, 1.0f, 1.0f

#define BC 1.0f // block coordinate

const float vertices[] = {
	 BC,  BC, BC,
	 BC, -BC, BC,
	-BC, -BC, BC,
	-BC,  BC, BC,
	 BC,  BC, -BC,
	 BC, -BC, -BC,
	-BC, -BC, -BC,
	-BC,  BC, -BC,

	C_BLUE,
	C_BLUE,
	C_BLUE,
	C_BLUE,
	C_BLUE,
	C_BLUE,
	C_BLUE,
	C_BLUE,
};

const GLshort indexData[] = {
	// front face
	0, 1, 2,
	0, 2, 3,

	// back face
	4, 5, 6,
	4, 6, 7,

	// top face
	0, 4, 7,
	7, 3, 0,

	// left face
	0, 4, 5,
	5, 1, 0,

	// right face
	3, 7, 6,
	6, 2, 3,

	// bottom face
	1, 5, 6,
	6, 2, 1,
};

#endif // MAIN_H







