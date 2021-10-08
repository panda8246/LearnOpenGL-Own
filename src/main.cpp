
//在包含其他头文件之前包含glad.h
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "GLFW//glfw3.h"

#include <iostream>

#include "shader.h"

GLFWwindow* window;
int Window_Width = 800;
int Window_Height = 600;

//三角形GL对象
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
Shader shader;

//顶点
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

//绘制索引
unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


//初始化三角形相关
void DrawInit() {
    
    //绑定顶点数据
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //索引
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader = Shader("shader/chapter1/vertex.v", "shader/chapter1/frag.f");
    
    glBindVertexArray(0);
}

void DrawTriangle() {
    glUseProgram(shader.ID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

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

    //渲染图形(默认)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //渲染线框
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//主循环
void Loop() {
    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        DrawTriangle();

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

    DrawInit();
	
    Loop();

    Quit();

}