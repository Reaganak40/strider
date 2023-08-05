#include "platformGL.h"
#include <stdio.h>
#include <stdlib.h>

#include "renderer/rendererGL.h"

namespace core {
	PlatformGL::PlatformGL()
		: window(nullptr), m_renderer(nullptr)
	{
		/* Initialize the library */
		if (!glfwInit()) {
			printf("Error: Failed to initialize GLFW.\n");
			exit(1);
		}
	}
	PlatformGL::~PlatformGL()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glClearError();
		glfwTerminate();
	}
	void PlatformGL::CreateWindow(const char* nWindowName, int nWindowWidth, int nWindowHeight)
	{
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(nWindowWidth, nWindowHeight, nWindowName, NULL, NULL);
		if (!window)
		{
			printf("Error: Failed to create GLFW Window.\n");
			glfwTerminate();
			exit(1);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		// Load all OpenGL functions using the glfw loader function
		// If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			printf("Failed to initialize OpenGL context\n");
			glfwTerminate();
			exit(1);
		}

		// glad populates global constants after loading to indicate,
		// if a certain extension/version is available.
		printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_renderer = std::make_unique<RendererGL>(nWindowWidth, nWindowHeight);
	}

	void PlatformGL::AddDefaultShader(int windowWidth, int windowHeight)
	{
		m_renderer->SetDefaultShader(windowWidth, windowHeight);
	}

	void PlatformGL::Clear()
	{
		m_renderer->Clear();
	}

	void PlatformGL::Draw(const SceneID& s_ID)
	{
		m_renderer->Draw(s_ID);
	}

	void PlatformGL::FinishDrawStep()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	void PlatformGL::SetBackgroundColor(float r, float g, float b, float a)
	{
		m_renderer->SetBackgroundColor(r, g, b, a);
	}
	bool PlatformGL::IsOpen()
	{
		return !glfwWindowShouldClose(window);
	}

	void PlatformGL::AddDrawLayer(const SceneID& s_ID, const LayerID& l_ID)
	{
		m_renderer->AddBatchBufferLayer(s_ID, l_ID);
	}

	Vertex* PlatformGL::GetMeshBatchLocation(const SceneID& s_ID, const LayerID& l_ID)
	{
		return m_renderer->GetBatchBufferVBO(s_ID, l_ID);
	}

	unsigned int PlatformGL::AddMesh(const SceneID& s_ID, const LayerID& l_ID, const Mesh& mesh)
	{
		return m_renderer->AddMesh(s_ID, l_ID, mesh);
	}

	void PlatformGL::AttachGui(const SceneID& s_ID, const LayerID& l_ID, GuiTemplate*& gui)
	{
		m_renderer->AttachGui(s_ID, l_ID, gui);
	}

	void PlatformGL::GuiNewFrame()
	{
		m_renderer->GuiNewFrame();
	}

	float PlatformGL::GetTime()
	{
		return  (float)glfwGetTime();
	}
}
