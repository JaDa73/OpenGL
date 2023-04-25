#include "Window.h"


Window::Window(){
    width = 800;
    height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight){
    width = windowWidth;
    height = windowHeight;
}

int Window::Initialise(){
    if (glfwInit() != GLFW_TRUE){
        printf("GLFW init failed!");
        glfwTerminate();
        return 1;
    }

    //Setup GKFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Core profile = No Backward Compatability
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Allow forward compatability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //Window context
    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

    if(!mainWindow){
        printf("GLFW window creation failure!");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extension features
    glewExperimental = GL_TRUE; 

    if(glewInit() != GLEW_OK){
        printf("GLEW init failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    //Setup viewport size
    glViewport(0,0, bufferWidth, bufferHeight);

    return 0;
}

Window::~Window(){

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

}
