#pragma once

#include "test.h"
#include "core.h"

namespace test {

	class TestSampler : public Test {
	private:
		GLFWwindow* window;

		Test* currentTest;
		float samplerWindowWidth;
		float samplerWindowHeight;
		int samplerWindowX;
		int samplerWindowY;
		int selectedTest;
	public:
		TestSampler(GLFWwindow* windowContext);
		~TestSampler();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		void AddTestOption(int buttonID);
		void StartNewTest();
	};
}