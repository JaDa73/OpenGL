#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{
public:    
    Window();
    Window(GLint windowWidth, GLint windowHeight);

    int Initialise();

    GLfloat getBufferWidth(){return bufferWidth;};
    GLfloat getBufferHeight(){return bufferHeight;};

    bool getShouldClose() {return glfwWindowShouldClose(mainWindow);};

    void swapBuffers() {glfwSwapBuffers(mainWindow);};

    ~Window();
private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;

    void createCallBacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
};