#include "core.h"
#include "app.h"
#include "scene.h"
#include "error.h"



namespace core {

	AppInstance::AppInstance(const char* nWindowName, int nWindowWidth, int nWindowHeight)
		: windowWidth(nWindowWidth), windowHeight(nWindowHeight)
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
			std::cout << "Failed to initialize OpenGL context" << std::endl;
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

		m_renderer.SetBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
		m_renderer.SetDefaultShader(nWindowWidth, nWindowHeight);
	}

	AppInstance::~AppInstance()
	{
	}

	void AppInstance::Update(float deltaTime)
	{
		/* Render here */
		m_renderer.Clear();

		if (m_currentScene->sceneCallBack.GuiIsAttached) {

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		m_currentScene->scenePtr->Update(deltaTime);
	}

	void AppInstance::Render()
	{
		if (m_currentScene) {
			m_renderer.Draw(m_currentScene->scenePtr);
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	std::shared_ptr<Scene> AppInstance::NewScene(SceneID name)
	{
		m_scenes[name] = { nullptr, { false } };
		std::shared_ptr<Scene> nScene = std::make_shared<Scene>(m_renderer, m_scenes[name].sceneCallBack);
		nScene->m_SceneID = name;
		nScene->m_VAO.Bind();
		nScene->AddLayer();

		if (m_currentScene) {
			m_currentScene->scenePtr->m_VAO.Bind();
		}

		m_scenes[name].scenePtr = nScene;
		return nScene;
	}
	std::shared_ptr<Scene> AppInstance::SetScene(SceneID name)
	{
		if (m_scenes.find(name) == m_scenes.end()) {
			NewScene(name);
		}

		m_currentScene = &m_scenes[name];
		m_currentScene->scenePtr->m_VAO.Bind();
		
		return m_currentScene->scenePtr;
	}
}

StriderEngine::StriderEngine()
	: app(nullptr)
{
	/* Initialize the library */
	if (!glfwInit()) {
		printf("Error: Failed to initialize GLFW.\n");
		exit(1);
	}
}

StriderEngine::~StriderEngine()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	delete app;

	glClearError();
	glfwTerminate();
}

int StriderEngine::CreateWindow(const char* nWindowName, int nWindowWidth, int nWindowHeight)
{
	app = new core::AppInstance(nWindowName, nWindowWidth, nWindowHeight);
	timestep.deltaTime = 0.0f;
	return 0;
}

void StriderEngine::Update()
{
	timestep.Update();
	app->Update(timestep.deltaTime);
}
