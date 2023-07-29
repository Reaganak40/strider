#include "testSampler.h"
#include "testClearColor.h"
#include "testQuad.h"

#include "error.h"

#define BUTTON_ID_TEST_CLEAR_COLOR 1
#define BUTTON_ID_TEST_QUAD 2

namespace test {

	TestSampler::TestSampler(GLFWwindow* windowContext)
		: Test(windowContext), currentTest(nullptr), selectedTest(0)
	{
		samplerWindowWidth = 250.0f;
		samplerWindowHeight = 400.0f;

		window = windowContext;
		glfwGetWindowSize(window, &samplerWindowX, &samplerWindowY);
		samplerWindowX -= (samplerWindowWidth + 10.0f);
		samplerWindowY =  10;
	}

	TestSampler::~TestSampler()
	{
		delete currentTest;
	}
	void TestSampler::OnUpdate(float deltaTime)
	{
		if (!currentTest && selectedTest) {
			StartNewTest();
		}
		else if (currentTest && currentTest->ShouldTerminate()) {
			delete currentTest;
			currentTest = nullptr;
			selectedTest = 0;
		}
		else if (currentTest && (selectedTest < 0)) {
			// restart test
			delete currentTest;
			selectedTest = -selectedTest;
			StartNewTest();
		}
		
		if (currentTest) {
			currentTest->OnUpdate(deltaTime);
		}
	}

	void TestSampler::OnRender()
	{
		if (currentTest) {
			currentTest->OnRender();
		}
	}
	void TestSampler::OnImGuiRender()
	{
		if (currentTest) {
			currentTest->OnImGuiRender();
		}

		ImGui::SetNextWindowSize(ImVec2(samplerWindowWidth, samplerWindowHeight), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(samplerWindowX, samplerWindowY), ImGuiCond_Once);
			
		ImGui::Begin("Test Sampler");
			
		AddTestOption(BUTTON_ID_TEST_CLEAR_COLOR);
		AddTestOption(BUTTON_ID_TEST_QUAD);
			
		ImGui::End();
	}

	void TestSampler::AddTestOption(int buttonID)
	{
		std::string text_label;
		std::string button_label;

		switch (buttonID) {
		case BUTTON_ID_TEST_CLEAR_COLOR:
			text_label = "Test Clear Color";
			break;
		case BUTTON_ID_TEST_QUAD:
			text_label = "Test Basic Quad ";
			break;
		default:
			text_label = "BAD IDENTIFIER!";
		}

		ImGui::PushID(buttonID);
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 1.0f, 1.0f, 1.0f });
		ImGui::Text(text_label.c_str());
		ImGui::SameLine();
		ImGui::PopStyleColor();

		if (selectedTest == buttonID) {
			button_label = "Restart Test";
		}
		else {
			button_label = "Start Test";
		}

		if (ImGui::Button(button_label.c_str())) {
			
			if (selectedTest == buttonID) {
				selectedTest = -selectedTest;
			}
			else if (selectedTest > 0) {
				delete currentTest;
				currentTest = nullptr;
				selectedTest = buttonID;
			}
			else {
				selectedTest = buttonID;
			}
		}
		ImGui::PopID();
	}

	void TestSampler::StartNewTest()
	{
		switch (selectedTest) {
		case BUTTON_ID_TEST_CLEAR_COLOR:
			currentTest = new TestClearColor();
			break;
		case BUTTON_ID_TEST_QUAD:
			currentTest = new TestBasicQuad(window);
			break;
		default:
			std::cout << "Warning: Unidentified selected test!\n";
		}
	}
}