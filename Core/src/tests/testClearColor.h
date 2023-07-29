#pragma once

#include "test.h"

namespace test {

	class TestClearColor : public Test {
	private:
		float clearColor[4];
		float oldColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}