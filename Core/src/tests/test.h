#pragma once
#include "core.h"

namespace test {

	class Test {
	
	public:
		Test() : shouldTerminate(false), window(nullptr) {};
		Test(GLFWwindow* windowContext) : shouldTerminate(false), window(windowContext) {};

		virtual ~Test() {};

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		bool ShouldTerminate() { return shouldTerminate; }
	protected:
		GLFWwindow* window;

		bool shouldTerminate;
		void ShowWindowFooter();
	};
}
