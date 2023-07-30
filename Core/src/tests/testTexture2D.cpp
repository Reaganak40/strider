#include "testTexture2D.h"
#include "core.h"
#include "error.h"

#include "vertexArray.h"
#include "shader.h"
#include "utils.h"

namespace test {



	TestTexture2D::TestTexture2D(GLFWwindow* windowContext)
		: Test(windowContext), quadColor{ 0.5f, 0.2f, 0.5f, 1.0f }
	{
		quadWidth = 450.0f;
		quadHeight = 300.0f;

		positions[0] = { {0.0f,		 0.0f,		 0.0f}, {0.0f,  0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} };
		positions[1] = { {quadWidth, 0.0f,		 0.0f}, {1.0f,  0.0f}, {0.0f, 0.0f, 0.0f, 1.0f} };
		positions[2] = { {quadWidth, quadHeight, 0.0f}, {1.0f,  1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} };
		positions[3] = { {0.0f,		 quadHeight, 0.0f}, {0.0f,  1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} };

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		ibo = RegisterIndexBuffer(indices, sizeof(indices));
		iboCount = sizeof(indices) / sizeof(IndexBufferCount);

		shader = CreateShader(ReadFile("resources/shaders/vertex.glsl"), ReadFile("resources/shaders/fragmentTex.glsl"));
		BindShader(shader);

		vao.Bind();
		vao.PushCRU_Data(positions, sizeof(Vertex_PTC), 4, ibo, iboCount, shader);

		uMVP = GetUniformVariable(shader, "uMVP");

		texture = LoadTexture("resources/textures/dragon.png");
		BindTexture(texture.id, 0);
		uTexture = GetUniformVariable(shader, "uTexture");
		SetUniform1i(uTexture, 0);

		glfwGetWindowSize(window, &maxX, &maxY);

		proj = glm::ortho(0.0f, (float)maxX, 0.0f, (float)maxY, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		translation = glm::vec3((maxX / 2) - (quadWidth / 2), 200, 0);

		maxX -= (int)quadWidth;
		maxY -= (int)quadHeight;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;

		SetUniformMat4f(uMVP, mvp);
	}

	TestTexture2D::~TestTexture2D()
	{
		glCall(glDeleteBuffers(1, &ibo));
		glCall(glDeleteTextures(1, &texture.id));
		glCall(glDeleteProgram(shader));
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;
		SetUniformMat4f(uMVP, mvp);
	}

	void TestTexture2D::OnRender()
	{
		vao.Bind();
		glCall(vao.DrawAll());
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SetNextWindowSize(ImVec2(368, 250), ImGuiCond_Appearing);
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);

		ImGui::Begin("Test Texure2D");

		ImGui::SliderFloat("Translation X", &translation.x, 0.0f, (float)maxX);
		ImGui::SliderFloat("Translation Y", &translation.y, 0.0f, (float)maxY);

		ShowWindowFooter();
		ImGui::End();
	}

}