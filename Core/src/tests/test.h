#pragma once

namespace test {

	class Test {
	
	public:
		Test() : shouldTerminate(false) {};
		virtual ~Test() {};

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		bool ShouldTerminate() { return shouldTerminate; }
	protected:
		bool shouldTerminate;
		void ShowWindowFooter();
	};
}
