#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800           // ���ڿ��
#define HEIGHT 600          // ���ڸ߶�
#define TITLE "LearnOpenGL" // ���ڱ���

// ������ɫ��Դ��
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

// Ƭ����ɫ��Դ��
const char *fragmentShaderSource =
    "#version 330 core\n"

    "in vec2 texCoord;\n"

    "uniform sampler2D ourTexture;\n"

    "out vec4 fragColor;\n"

    "void main()\n"
    "{\n"
    "    fragColor = texture(ourTexture, texCoord);\n"
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

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

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

    // �������󶨶����������
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // ���������ö��㻺�����
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ���ö���λ������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���ö�����ɫ����ָ��
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ������������
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // ���ز���������
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../Resource/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // ��Ⱦѭ��
    while (! glfwWindowShouldClose(window))
    {
        // ����
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ʹ����ɫ������
        glUseProgram(shaderProgram);

        // ����mvp����
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

        // ������
        glBindTexture(GL_TEXTURE_2D, texture);

        // �󶨶����������
        glBindVertexArray(VAO);

        // ��ʼ����
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ������ɫ����
        glfwSwapBuffers(window);

        // �����¼�
        glfwPollEvents();
    }

    // �ͷŶ����������
    glDeleteVertexArrays(1, &VAO);

    // �ͷŶ��㻺�����
    glDeleteBuffers(1, &VBO);

    // �ͷ���ɫ���������
    glDeleteProgram(shaderProgram);

    // �ͷ���Դ
    stbi_image_free(data);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // �����ӿڵ�����ͳߴ�
    glViewport(0, 0, width, height);
}