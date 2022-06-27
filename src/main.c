#include "../include/main.h"

int main(int argc, char *argv[]) {
    initializeGLFW();
    GLFWwindow* window = buildWindow();
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    shaderProgram = buildShaders();
    unsigned int offsetUniform = glGetUniformLocation(shaderProgram, "offset");
    unsigned int perspectiveMatrixUnif = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
    float fFrustumScale = 1.0f;
    float fzNear = 0.5f;
    float fzFar = 3.0f;
    memset(mPerspective, 0, sizeof(float) * 16);

    mPerspective[0] = fFrustumScale / (WIDTH / (float) HEIGHT);
    mPerspective[5] = fFrustumScale;
    mPerspective[10] = (fzFar + fzNear) / (fzNear - fzFar);
    mPerspective[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    mPerspective[11] = -1.0f;
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, mPerspective);
    glUseProgram(0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

//     glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // to see wireframe

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

void display(GLFWwindow* window, unsigned int shaderProgram) {
    keyboard(window);

    /*
    float *fOffsets = (float*) calloc(2, sizeof(float));
    ComputePositionOffsets(fOffsets);
    AdjustVertexData(fOffsets);
    free(fOffsets);
    */

    glClearColor(bg_rgb[0], bg_rgb[1], bg_rgb[2], bg_rgb[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    unsigned int offsetUniform = glGetUniformLocation(shaderProgram, "offset");
    glUniform2f(offsetUniform, 0.5f, 0.5f);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    size_t colorStart = sizeof(vertices) / 2;
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) (colorStart));

    glDrawArrays(GL_TRIANGLES, 0, 36);

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
    float fFrustumScale = 1.0f;
    mPerspective[0] = fFrustumScale / (width / (float) height);
    mPerspective[5] = fFrustumScale;

    glUseProgram(shaderProgram);
    unsigned int perspectiveMatrixUnif = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, mPerspective);
    glUseProgram(0);

    glViewport(0, 0, width, height);
}

void ComputePositionOffsets(float *fOffsets) {
    const float fLoopDuration = 0.005f;
    const float fScale = TAU / fLoopDuration;
    float fElapsedTime = glfwGetTime() / 1000.0f;
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    fOffsets[0] = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    fOffsets[1] = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

void AdjustVertexData(float *fOffsets) {
    size_t colorStart = sizeof(vertices) / 2;
    float *fNewData = malloc(sizeof(float) * colorStart - 1);
    memcpy(&fNewData[0], vertices, colorStart - 1);
    int nLength = ((sizeof(vertices) / 2) - 1) / sizeof(float);
    for(int i=0; i<nLength; i+=4) {
        fNewData[i] += fOffsets[0];
        fNewData[i+1] += fOffsets[1];
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, colorStart - 1, &fNewData[0]);
}
