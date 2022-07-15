#ifndef MAIN_H
#define MAIN_H

// my files
#include "../include/utility.h"
#include "../include/matrix.h"
#include "../include/vector.h"
#include "../include/cube.h"

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

#define C_RED   1.0f, 0.0f, 0.0f, 1.0f
#define C_GREEN 0.0f, 1.0f, 0.0f, 1.0f
#define C_BLUE  0.0f, 0.0f, 1.0f, 1.0f

struct Cube** vCubes;

float *vertices;

const unsigned short indexData[] = {
	// front
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,
	// back
	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
	// bottom
	1, 6, 5,
	1, 2, 6,
	2, 1, 5,
	5, 6, 2,
	// top
	0, 7, 4,
	0, 3, 7,
	3, 4, 7,
	3, 0, 4,
	// right
	1, 0, 4,
	4, 5, 1,
	0, 1, 5,
	5, 4, 0,
	// left
	6, 7, 3,
	3, 2, 6,
	6, 2, 7,
	7, 2, 3,
};

#endif // MAIN_H
