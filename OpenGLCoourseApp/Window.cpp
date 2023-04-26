#include "Window.h"


Window::Window(){
    width = 800;
    height = 600;

    for(size_t i=0; i < 1024; i++){
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight){
    width = windowWidth;
    height = windowHeight;

    for(size_t i=0; i < 1024; i++){
        keys[i] = 0;
    }
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

    // Handle key + Mouse input
    createCallBacks();

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

    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}

void Window::createCallBacks(){
    glfwSetKeyCallback(mainWindow, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode){

    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < 1024){
        if(action == GLFW_PRESS){
            theWindow->keys[key] = true;
            printf("Pressed %d\n", key);
        } else if(action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
            printf("Released %d\n", key);
        }
    }

}

Window::~Window(){

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

}
