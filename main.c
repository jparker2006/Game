#include "main.h"

int main() {
    initializeGLFW();
    GLFWwindow* window = buildWindow();
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }
    unsigned int shaderProgram = buildShaders();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        display(window, shaderProgram);
    }
    glfwTerminate();
    return 0;
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

void display(GLFWwindow* window, unsigned int shaderProgram) {
    keyboard(window);

    float *fOffsets = (float*) calloc(2, sizeof(float));
    ComputePositionOffsets(fOffsets);
    AdjustVertexData(fOffsets);
    free(fOffsets);

    glClearColor(bg_rgb[0], bg_rgb[1], bg_rgb[2], bg_rgb[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
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
    glViewport(0, 0, width, height);
}

void ComputePositionOffsets(float *fOffsets) {
    const float fLoopDuration = 0.005f;
    const float fScale = PI * 2.0f / fLoopDuration;
    float fElapsedTime = glfwGetTime() / 1000.0f;
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    fOffsets[0] = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    fOffsets[1] = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

void AdjustVertexData(float *fOffsets) {
    float *fNewData = malloc(sizeof(float) * sizeof(vertices));
    memcpy(&fNewData[0], vertices, sizeof(vertices));
    int nLength = sizeof(vertices) / sizeof(float);
    for(int i=0; i<nLength; i+=3) {
        fNewData[i] += fOffsets[0];
        fNewData[i+1] += fOffsets[1];
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &fNewData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
