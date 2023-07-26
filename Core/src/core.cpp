#include "core.h"
#include "shader.h"
#include "error.h"
#include "utils.h"
#include "renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Load all OpenGL functions using the glfw loader function
    // If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    {
        CoreRenderUnit crUnit;

        VertexBuffer2f positions[4] = {
            {-0.5f, -0.5f}, // 0
            { 0.5f, -0.5f}, // 1
            { 0.5f,  0.5f}, // 2
            {-0.5f,  0.5f}, // 3
        };

        IndexBuffer indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        crUnit.vbo = RegisterVertexBuffer(positions, sizeof(positions));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        
        crUnit.ibo = RegisterIndexBuffer(indices, sizeof(indices));
        crUnit.iboCount = sizeof(indices) / sizeof(IndexBufferCount);

        crUnit.shader = CreateShader(ReadFile("resources/shaders/vertex.glsl"), ReadFile("resources/shaders/fragment.glsl"));
        BindShader(crUnit.shader);

        int location = glGetUniformLocation(crUnit.shader, "uColor");
        glCall(glUniform4f(location, 0.9f, 0.0f, 0.4f, 1.0f));

        float rValue = 0.9f;
        float increment = 0.01f;

        Renderer renderer;
        renderer.SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            renderer.Draw(crUnit);

            glUniform4f(location, rValue, 0.0f, 0.4f, 1.0f);

            rValue += increment;
            if (rValue >= 1.0f || rValue <= 0) {
                increment = -increment;
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(crUnit.shader);
    }
    glfwTerminate();
    return 0;
}