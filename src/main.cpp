
//在包含其他头文件之前包含glad.h
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "GLFW//glfw3.h"

#include <iostream>

GLFWwindow* window;
int Window_Width = 800;
int Window_Height = 600;

//三角形GL对象
unsigned int VBO;
unsigned int VAO;
unsigned int shader;

//三角形顶点
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

//shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";


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

    shader = glCreateProgram();
    int success;
    char infoLog[512];
    //Load Vertex
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //Load Fragment
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //Link
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragShader);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    
}

void DrawTriangle() {
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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