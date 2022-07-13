#include "../include/main.h"

float velo = -0.01f, accel = 0.0f, grav = -0.005f;

float ComputeAngleRad(float fElapsedTime, float fLoopDuration) {
    const float fScale = TAU / fLoopDuration;
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    return fCurrTimeThroughLoop * fScale;
}

int main(int argc, char *argv[]) {
    initializeGLFW();
    GLFWwindow* window = buildWindow();
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // camera matrice & shaders init
    shaderProgram = buildShaders();
    unsigned int modelToCameraMatrixUnif = glGetUniformLocation(shaderProgram, "modelToCameraMatrix");
    unsigned int cameraToClipMatrixUnif = glGetUniformLocation(shaderProgram, "cameraToClipMatrix");
    float fzNear = 1.0f;
    float fzFar = 61.0f;
    float fFrustumScale = frustumScale(45.0f);
    cameraToClipMatrix = mat_identity(4);
    cameraToClipMatrix->data[0] = fFrustumScale;
    cameraToClipMatrix->data[5] = fFrustumScale;
    cameraToClipMatrix->data[10] = (fzFar + fzNear) / (fzNear - fzFar);
    cameraToClipMatrix->data[11] = -1.0f;
    cameraToClipMatrix->data[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, &cameraToClipMatrix->data[0]);
    glUseProgram(0);

    // VBO & IBO inits
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // VAO inits
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    size_t colorDataOffset = sizeof(float) * 3 * numberOfVertices;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) colorDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBindVertexArray(0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);

    glEnable(GL_DEPTH_CLAMP);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // to see wireframe
    while (!glfwWindowShouldClose(window)) {
        display(window, shaderProgram);
    }

    glfwTerminate();
    return 0;
}

void display(GLFWwindow* window, unsigned int shaderProgram) {
    keyboard(window);

    glClearColor(bg_rgb[0], bg_rgb[1], bg_rgb[2], bg_rgb[3]);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int lnIBO = sizeof(indexData) / sizeof(const GLshort);
    unsigned int modelToCameraMatrixUnif = glGetUniformLocation(shaderProgram, "modelToCameraMatrix");

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    float fElapsedTime = glfwGetTime();
    float fAngRad = ComputeAngleRad(fElapsedTime, 3.0f);

    struct Matrix *rx = mat_ry(0.26);
//     printf("%f\n", fAngRad / TAU);

//     struct Matrix *rx = mat_identity(4);
    rx->data[13] = -3.4f;
    rx->data[14] = -14.0f;

//     struct Matrix *rx = mat_rz(fAngRad);
//     rx->data[14] = -4.0f;
//     rx->data[13] = 1.0f;
//     accel += grav;
//     rx->data[13] += velo;
//     velo += accel;
//     accel = 0.0f;
//     if (rx->data[13] < -1.0f) {
//         mat_delete(rx);
//         rx = mat_identity(4);
//         rx->data[13] = -1.0f;
//         rx->data[14] = -4.0f;
//     }

    glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, &rx->data[0]);
    glDrawElements(GL_TRIANGLES, lnIBO, GL_UNSIGNED_SHORT, 0);

    mat_delete(rx);

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void initializeGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* buildWindow() {
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", NULL, NULL);
    if (NULL == window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_window);
    return window;
}

unsigned int buildShaders() {
    const char *vertexShaderSource = LoadFile("/home/jparker/SomethingOpenGL/shaders/standard.vert");
    const char *fragmentShaderSource = LoadFile("/home/jparker/SomethingOpenGL/shaders/standard.frag");
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf("%s\n", infoLog);
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
       printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
       printf("%s\n", infoLog);
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        printf("%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void keyboard(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        printf("W\n");
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        printf("A\n");
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        printf("S\n");
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        printf("D\n");
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void resize_window(GLFWwindow* window, int width, int height) {
    float fFrustumScale = frustumScale(45.0f);
    cameraToClipMatrix->data[0] = fFrustumScale / (width / (float) height);
    cameraToClipMatrix->data[5] = fFrustumScale;
    glUseProgram(shaderProgram);
    unsigned int cameraToClipMatrixUnif = glGetUniformLocation(shaderProgram, "cameraToClipMatrix");
    glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, &cameraToClipMatrix->data[0]);
    glUseProgram(0);
    glViewport(0, 0, width, height);
}
