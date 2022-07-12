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
void ComputePositionOffsets(float *fOffsets); // fOffsets[0] = x offset, fOffsets[1] = y offset
void AdjustVertexData(float *fOffsets);

const int numberOfVertices = 8;

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertices[] = {
	+1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,

	GREEN_COLOR,
	BLUE_COLOR,
	RED_COLOR,
	BROWN_COLOR,
};

const GLshort indexData[] =
{
//Object 1
	0, 1, 2,
	1, 0, 3,
	2, 3, 0,
	3, 2, 1,

	5, 4, 6,
	4, 5, 7,
	7, 6, 4,
	6, 7, 5,
};

#endif // MAIN_H
