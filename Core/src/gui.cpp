#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "gui.h"


void GuiTemplate::RenderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DiagnosticsGUI::OnUpdate(float deltaTime)
{
}

void DiagnosticsGUI::OnRender()
{
	ImGui::SetNextWindowSize(ImVec2(295, 120), ImGuiCond_Appearing);
	ImGui::Begin("Diagnostic Tools");
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::Text("Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	RenderImGui();
}
