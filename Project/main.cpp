#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800           // ���ڿ��
#define HEIGHT 600          // ���ڸ߶�
#define TITLE "LearnOpenGL" // ���ڱ���

// ������ɫ��Դ��
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"

    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

// Ƭ����ɫ��Դ��
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
    "    fragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n";

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

    // ���ô��ڵ�������
    glfwMakeContextCurrent(window);

    // ע�ᴰ�ڳߴ�仯�Ļص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ��ʼ��GLAD, ���ڹ���OpenGL�ĺ���ָ��
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // ����������ɫ������
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // ��������ɫ��Դ�븽�ӵ�������ɫ��������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // ���붥����ɫ��Դ��
    glCompileShader(vertexShader);

    // ����Ƭ����ɫ������
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // ��Ƭ����ɫ��Դ�븽�ӵ�Ƭ����ɫ��������
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // ����Ƭ����ɫ��Դ��
    glCompileShader(fragmentShader);

    // ������ɫ���������
    unsigned int shaderProgram = glCreateProgram();

    // ��������ɫ�����󸽼ӵ���ɫ��������
    glAttachShader(shaderProgram, vertexShader);

    // ��Ƭ����ɫ�����󸽼ӵ���ɫ��������
    glAttachShader(shaderProgram, fragmentShader);

    // ������ɫ������
    glLinkProgram(shaderProgram);

    // �ͷŶ�����ɫ������
    glDeleteShader(vertexShader);

    // �ͷ�Ƭ����ɫ������
    glDeleteShader(fragmentShader);

    // ��ʼ����������
    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // ��ʼ����������
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // �������󶨶����������
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // ���������ö��㻺�����
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���������������������
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // ��Ⱦѭ��
    while (! glfwWindowShouldClose(window))
    {
        // ʹ����ɫ������
        glUseProgram(shaderProgram);

        // �󶨶����������
        glBindVertexArray(VAO);

        // ���յ�ǰ�󶨵�������������е��������л���
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ������ɫ����
        glfwSwapBuffers(window);

        // �����¼�
        glfwPollEvents();
    }

    // �ͷŶ����������
    glDeleteVertexArrays(1, &VAO);

    // �ͷŶ��㻺�����
    glDeleteBuffers(1, &VBO);

    // �ͷ������������
    glDeleteBuffers(1, &EBO);

    // �ͷ���ɫ���������
    glDeleteProgram(shaderProgram);

    // �ͷ���Դ
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // �����ӿڵ�����ͳߴ�
    glViewport(0, 0, width, height);
}