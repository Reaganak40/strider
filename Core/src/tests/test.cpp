#include "test.h"
#include "core.h"

namespace test {

	void Test::ShowWindowFooter()
	{
		auto windowHeight = ImGui::GetWindowSize().y;
		auto textHeight = ImGui::CalcTextSize("Text").y;

		ImGui::SetCursorPosY((windowHeight - textHeight) - 15);

		ImGui::Text("Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SameLine();

		if (ImGui::Button("End Test") && !shouldTerminate) {
			shouldTerminate = true;
		}
	}
}