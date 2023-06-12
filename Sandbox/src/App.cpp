#include <memory>

#include "Core.h"

using namespace Core;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() = default;
	virtual ~ExampleLayer() = default;

	//std::unique_ptr<Framebuffer> FBO;

	virtual void OnAttach()
	{
		Shader::LoadShaders({ "Model", "Light" });

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		BufferLayout bufferLayout =
		{
			{ "a_Position", ShaderDataType::Float3}
		};

		//FBO = Framebuffer::Create({ 1280, 720 });

		Renderer::AddShape("LightCube", "Light", vertices, sizeof(vertices), bufferLayout, glm::mat4(1.0f));
	}

	virtual void Update() override
	{
		//FBO->Bind();
		//FBO->Unbind();

		Renderer::BeginScene();

		glm::vec3 lightPos = { 3.0f, 5.0f, 3.0f };
		lightPos.x *= cos(Application::GetTime());
		lightPos.z *= sin(Application::GetTime());

		// Model stuff
		//Shader::UploadUniform("Model", "ViewProjection", m_Camera->GetViewProjectionMatrix());
		//Shader::UploadUniform("Model", "Transform", glm::mat4(1.0f));
		//Shader::UploadUniform("Model", "ViewPos", m_Camera->GetPosition());
		//Shader::UploadUniform("Model", "material.shininess", 32.0f);

		Shader::UploadUniform("Model", "light.position", lightPos);
		Shader::UploadUniform("Model", "light.color", glm::vec3(1.0f, 1.0f, 1.0f));
		Shader::UploadUniform("Model", "light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		Shader::UploadUniform("Model", "light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		Shader::UploadUniform("Model", "light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, lightPos);
		transform = glm::scale(transform, glm::vec3(0.2f));

		Renderer::UpdateShapeTransform("LightCube", transform);
		Renderer::Draw();

		Renderer::EndScene();
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