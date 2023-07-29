#include "testClearColor.h"

#include "core.h"
#include "error.h"

namespace test {



	TestClearColor::TestClearColor()
		: clearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
		glCall(glGetFloatv(GL_COLOR_CLEAR_VALUE, oldColor));
	}

	TestClearColor::~TestClearColor()
	{
		glCall(glClearColor(oldColor[0], oldColor[1], oldColor[2], oldColor[3]));
		std::cout << "Destructor called\n";
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::OnRender()
	{
		glCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::SetNextWindowSize(ImVec2(368, 100), ImGuiCond_Appearing);
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
		ImGui::Begin("Test Clear Color");
		ImGui::ColorEdit4("Clear Color", clearColor);
		ShowWindowFooter();

		ImGui::End();
	}

}