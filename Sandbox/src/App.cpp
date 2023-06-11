#include <memory>

#include "Core.h"

using namespace Core;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() = default;
	virtual ~ExampleLayer() = default;

	std::unique_ptr<Framebuffer> FBO;
	virtual void OnAttach()
	{
		FBO = Framebuffer::Create({ 1280, 720 });
	}

	virtual void Update() override
	{
		FBO->Bind();
		FBO->Unbind();
	}

	virtual void OnGuiRender() override
	{
		// Main window flags
		//ImGuiWindowFlags windowFlags =
		//	ImGuiWindowFlags_MenuBar |
		//	ImGuiWindowFlags_NoDocking |
		//	ImGuiWindowFlags_NoTitleBar |
		//	ImGuiWindowFlags_NoCollapse |
		//	ImGuiWindowFlags_NoResize |
		//	ImGuiWindowFlags_NoMove |
		//	ImGuiWindowFlags_NoBringToFrontOnFocus |
		//	ImGuiWindowFlags_NoNavFocus;

		//ImGuiWindowFlags subWindowFlags = 
		//	ImGuiWindowFlags_NoMove |
		//	ImGuiWindowFlags_NoScrollbar |
		//	ImGuiWindowFlags_NoScrollWithMouse |
		//	ImGuiWindowFlags_NoTitleBar |
		//	ImGuiWindowFlags_NoCollapse;

		ImGuiWindowFlags windowFlags =
			ImGuiWindowFlags_MenuBar;

		ImGuiWindowFlags subWindowFlags =
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse;

		// Main window configs
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		// Create main window for dockspace
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
		ImGui::Begin("Dockspace demo", (bool*)true, windowFlags);

		// Crate dockspace
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_NoResize);

		ImGui::Begin("Properties", (bool*)true, subWindowFlags);
		ImGui::Text("This is a properties panel!");
		ImGui::End();

		ImGui::Begin("Viewport", (bool*)true, subWindowFlags);
		// TODO
		//uint32_t textureID = FBO->GetColorAttachmentRendererID();
		//ImGui::Image((void*)textureID, ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		// End main window
		ImGui::End();
		ImGui::PopStyleVar();
	}
};

class App : public Application
{
public:
	App()
		: Application({"MarkkuTheLoader", 1280, 720})
	{
		PushLayer(new ExampleLayer());
	}
};

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
}