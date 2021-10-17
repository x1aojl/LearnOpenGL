#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "LearnOpenGL"

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
    if (window != NULL)
    {
        // 设置窗口的上下文
        glfwMakeContextCurrent(window);

        // 注册窗口尺寸变化的回调函数
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // 初始化GLAD, 用于管理OpenGL的函数指针
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            // 渲染循环
            while (!glfwWindowShouldClose(window))
            {
                // 交换颜色缓冲
                glfwSwapBuffers(window);

                // 处理事件
                glfwPollEvents();
            }
        }
    }

    // 释放资源
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 设置视口的坐标和尺寸
    glViewport(0, 0, width, height);
}