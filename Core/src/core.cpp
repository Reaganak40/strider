#include "core.h"
#include "shader.h"
#include "error.h"
#include "utils.h"
#include "texture.h"
#include "renderer.h"
#include "vertexArray.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
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
        VertexArray vao;

        Texture texture;

        Vertex_PTC positions[4] = {
            { { 100.0f, 100.0f, 0.0f}, {0.0f,  0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, // 0
            { { 300.0f, 100.0f, 0.0f}, {1.0f,  0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, // 1
            { { 300.0f, 300.0f, 0.0f}, {1.0f,  1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, // 2
            { { 100.0f, 300.0f, 0.0f}, {0.0f,  1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} }, // 3
        };

        IndexBuffer indices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        
        IndexBufferID ibo = RegisterIndexBuffer(indices, sizeof(indices));
        IndexBufferCount iboCount = sizeof(indices) / sizeof(IndexBufferCount);
        
        

        ShaderID shader = CreateShader(ReadFile("resources/shaders/vertex.glsl"), ReadFile("resources/shaders/fragment.glsl"));
        BindShader(shader);

        vao.Bind();
        vao.PushCRU_Data(positions, sizeof(Vertex_PTC), 4, ibo, iboCount, shader);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        texture = LoadTexture("resources/textures/dragon.png");
        BindTexture(texture.id, 0);
        
        UniformVariable uTexture = GetUniformVariable(shader, "uTexture");
        SetUniform1i(uTexture, 0);

        UniformVariable uMVP = GetUniformVariable(shader, "uMVP");

        UniformVariable uColor = GetUniformVariable(shader, "uColor");
        SetUniform4f(uColor, 1.0f, 1.0f, 0.0f, 1.0f);

        Renderer::SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::vec3 translation(200, 200, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            SetUniformMat4f(uMVP, mvp);
            
            vao.DrawAll();

            ImGui::Begin("Debug");
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1280.0f);
            ImGui::Text("App Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();


        glDeleteBuffers(1, &ibo);
        glDeleteProgram(shader);
    }

    glClearError();
    glfwTerminate();
    return 0;
}