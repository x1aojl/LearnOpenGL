#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "LearnOpenGL"

// ���ڳߴ�仯�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // ��ʼ��GLFW, ʹ��OpenGL3.3�汾�ĺ���ģʽ
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ��������
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (window != NULL)
    {
        // ���ô��ڵ�������
        glfwMakeContextCurrent(window);

        // ע�ᴰ�ڳߴ�仯�Ļص�����
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // ��ʼ��GLAD, ���ڹ���OpenGL�ĺ���ָ��
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            // ��Ⱦѭ��
            while (!glfwWindowShouldClose(window))
            {
                // ������ɫ����
                glfwSwapBuffers(window);

                // �����¼�
                glfwPollEvents();
            }
        }
    }

    // �ͷ���Դ
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // �����ӿڵ�����ͳߴ�
    glViewport(0, 0, width, height);
}