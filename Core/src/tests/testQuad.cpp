#include "testQuad.h"
#include "core.h"
#include "error.h"

#include "vertexArray.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"

namespace test {



	TestBasicQuad::TestBasicQuad(GLFWwindow* windowContext)
		: Test(windowContext), quadColor{0.5f, 0.2f, 0.5f, 1.0f}
	{
		quadWidth = 200.0f;
		quadHeight = 200.0f;

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
		
		shader = CreateShader(ReadFile("resources/shaders/vertex.glsl"), ReadFile("resources/shaders/fragment.glsl"));
		BindShader(shader);

		vao.Bind();
		vao.PushCRU_Data(positions, sizeof(Vertex_PTC), 4, ibo, iboCount, shader);

		uMVP = GetUniformVariable(shader, "uMVP");

		uColor = GetUniformVariable(shader, "uColor");

		glfwGetWindowSize(window, &maxX, &maxY);

		proj = glm::ortho(0.0f, (float)maxX, 0.0f, (float)maxY, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		translation = glm::vec3((maxX/2)-(quadWidth/2), 200, 0);

		maxX -= quadWidth;
		maxY -= quadHeight;
	}

	TestBasicQuad::~TestBasicQuad()
	{
		glCall(glDeleteBuffers(1, &ibo));
		glCall(glDeleteProgram(shader));
	}

	void TestBasicQuad::OnUpdate(float deltaTime)
	{
		SetUniform4f(uColor, quadColor[0], quadColor[1], quadColor[2], quadColor[3]);
	}

	void TestBasicQuad::OnRender()
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model;

		SetUniformMat4f(uMVP, mvp);

		vao.Bind();
		glCall(vao.DrawAll());
	}

	void TestBasicQuad::OnImGuiRender()
	{
		ImGui::SetNextWindowSize(ImVec2(368, 250), ImGuiCond_Appearing);
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
		
		ImGui::Begin("Test Basic Quad");
		ImGui::SliderFloat("Translation X", &translation.x, 0.0f, maxX);
		ImGui::SliderFloat("Translation Y", &translation.y, 0.0f, maxY);

		ImGui::NewLine();
		ImGui::ColorEdit4("Quad Color", quadColor);

		ShowWindowFooter();
		ImGui::End();
	}

}