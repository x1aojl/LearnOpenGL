#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800           // 窗口宽度
#define HEIGHT 600          // 窗口高度
#define TITLE "LearnOpenGL" // 窗口标题

// 顶点着色器源码
const char *vertexShaderSource =
    "#version 330 core\n"

    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"

    "layout(location = 0) in vec3 aPos;\n"
    "layout(location = 1) in vec2 aTexCoord;\n"

    "out vec2 texCoord;\n"

    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
    "    texCoord = aTexCoord;\n"
    "}\n";

// 片断着色器源码
const char *fragmentShaderSource =
    "#version 330 core\n"

    "in vec2 texCoord;\n"

    "uniform sampler2D ourTexture;\n"

    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
    "    fragColor = texture(ourTexture, texCoord);\n"
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

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

    // 设置顶点位置属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 设置顶点颜色属性指针
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 创建并绑定纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../Resource/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 渲染循环
    while (! glfwWindowShouldClose(window))
    {
        // 清屏
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);

        // 计算mvp矩阵
        glm::mat4 model, view, projection;
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
        unsigned int projectionLocation = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, texture);

        // 绑定顶点数组对象
        glBindVertexArray(VAO);

        // 开始绘制
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 交换颜色缓冲
        glfwSwapBuffers(window);

        // 处理事件
        glfwPollEvents();
    }

    // 释放顶点数组对象
    glDeleteVertexArrays(1, &VAO);

    // 释放顶点缓冲对象
    glDeleteBuffers(1, &VBO);

    // 释放着色器程序对象
    glDeleteProgram(shaderProgram);

    // 释放资源
    stbi_image_free(data);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 设置视口的坐标和尺寸
    glViewport(0, 0, width, height);
}