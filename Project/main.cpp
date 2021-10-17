#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800           // 窗口宽度
#define HEIGHT 600          // 窗口高度
#define TITLE "LearnOpenGL" // 窗口标题

// 顶点着色器源码
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"

    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

// 片断着色器源码
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
    "    fragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n";

// 窗口尺寸变化的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // 初始化GLFW, 使用OpenGL3.3版本的核心模式
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    // 设置窗口的上下文
    glfwMakeContextCurrent(window);

    // 注册窗口尺寸变化的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化GLAD, 用于管理OpenGL的函数指针
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 创建顶点着色器对象
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // 将顶点着色器源码附加到顶点着色器对象上
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // 编译顶点着色器源码
    glCompileShader(vertexShader);

    // 创建片断着色器对象
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 将片断着色器源码附加到片断着色器对象上
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // 编译片断着色器源码
    glCompileShader(fragmentShader);

    // 创建着色器程序对象
    unsigned int shaderProgram = glCreateProgram();

    // 将顶点着色器对象附加到着色器对象上
    glAttachShader(shaderProgram, vertexShader);

    // 将片断着色器对象附加到着色器对象上
    glAttachShader(shaderProgram, fragmentShader);

    // 链接着色器程序
    glLinkProgram(shaderProgram);

    // 释放顶点着色器对象
    glDeleteShader(vertexShader);

    // 释放片断着色器对象
    glDeleteShader(fragmentShader);

    // 初始化顶点数据
    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // 初始化索引数组
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // 创建并绑定顶点数组对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 创建并设置顶点缓冲对象
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建并设置索引缓冲对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // 渲染循环
    while (! glfwWindowShouldClose(window))
    {
        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 绑定顶点数组对象
        glBindVertexArray(VAO);

        // 按照当前绑定的索引缓冲对象中的索引进行绘制
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 交换颜色缓冲
        glfwSwapBuffers(window);

        // 处理事件
        glfwPollEvents();
    }

    // 释放顶点数组对象
    glDeleteVertexArrays(1, &VAO);

    // 释放顶点缓冲对象
    glDeleteBuffers(1, &VBO);

    // 释放索引缓冲对象
    glDeleteBuffers(1, &EBO);

    // 释放着色器程序对象
    glDeleteProgram(shaderProgram);

    // 释放资源
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 设置视口的坐标和尺寸
    glViewport(0, 0, width, height);
}