
//在包含其他头文件之前包含glad.h
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "GLFW//glfw3.h"

#include <iostream>

GLFWwindow* window;
int Window_Width = 800;
int Window_Height = 600;

//窗口改变回调
void Framebuffer_size_callback(GLFWwindow* _window, int width, int height) {
    Window_Width = width;
    Window_Height = height;
    glViewport(0, 0, width, height);
}

void GLInit() {
    
    //glfw初始化
    glfwInit();

    //OpenGL版本设置为3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //OpenGL Core模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Mac OS 需要这行代码
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(Window_Width, Window_Height, "Learn OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();    //关闭
        std::cout << "Failed to create a GLFW window." << std::endl;
        return;
    }

    //设置窗口上下文
    glfwMakeContextCurrent(window);

    //初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return;
    }
    
    //渲染窗口
    glViewport(0, 0, Window_Width, Window_Height);
    //设置窗口回调
    glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);
}

//主循环
void Loop() {
    while (!glfwWindowShouldClose(window)) 
    {
        //双缓冲模式下，交换缓冲，将绘制的图像输出到屏幕
        glfwSwapBuffers(window);
        //检查事件，是回调的入口
        glfwPollEvents();
    }
}

//退出
void Quit() {
    glfwTerminate();
}

int main(){

    GLInit();
	
    Loop();

    Quit();

}