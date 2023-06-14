#include <memory>

#include "Core.h"

#include "SettingsPanel.h"

using namespace Core;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() = default;
	virtual ~ExampleLayer() = default;

	virtual void OnAttach()
	{
		m_Framebuffer = Framebuffer::Create({ 1280, 720 });

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

		Renderer::AddShape("LightCube", "Light", vertices, sizeof(vertices), bufferLayout, glm::mat4(1.0f));
	}

	virtual void Update() override
	{
		m_Framebuffer->Bind();

		Renderer::BeginScene();

		// Update model's uniforms
		Shader::UploadUniform("Model", "ViewProjection", Camera::GetViewProjectionMatrix());

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_ModelRotation.x, { 1, 0, 0 })
			* glm::rotate(glm::mat4(1.0f), m_ModelRotation.y, { 0, 1, 0 })
			* glm::rotate(glm::mat4(1.0f), m_ModelRotation.z, { 0, 0, 1 });
		glm::mat4 modelTransform = glm::translate(glm::mat4(1.0f), m_ModelPos) * rotation * glm::scale(glm::mat4(1.0f), m_ModelScale);

 		Shader::UploadUniform("Model", "Transform", modelTransform);
		Shader::UploadUniform("Model", "material.shininess", 32.0f);

		glm::vec3 lightColor = m_LightColor / glm::vec3(255);

		// Update light's uniforms
		Lighting::SetLight("Model",
		{
			m_LightPos,
			lightColor,
			glm::vec3(m_LightAmbient),
			glm::vec3(m_LightDiffuse),
			glm::vec3(m_LightSpecular)
		});

		glm::mat4 lightTransform = glm::translate(glm::mat4(1.0f), m_LightPos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
		//Renderer::UpdateUniforms("LightCube", "Transform", lightTransform);
		Renderer::UpdateShapeTransform("LightCube", lightTransform);
		Renderer::UpdateShapeColor("LightCube", lightColor);

		// Draw
		Renderer::Draw();
		Model::Draw();

		Renderer::EndScene();
		m_Framebuffer->Unbind();
	}

	virtual void OnGuiRender() override
	{
		// Window flags
		ImGuiWindowFlags windowFlags =
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoNavFocus;

		ImGuiWindowFlags subWindowFlags = 
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse;

		// Main window configs
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		// Create main window for dockspace
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 10, 10 });
		ImGui::Begin("Dockspace demo", (bool*)true, windowFlags);

		// Crate dockspace
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_AutoHideTabBar);

		// Properties
		ImGui::Begin("Properties", (bool*)true, subWindowFlags);

		// Model settings
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 20 });
		ImGui::PushTextWrapPos(350.0f);
		ImGui::TextWrapped("MarkkuTheLoader - 3D Model loader. Load model by typing its name (ex. dog.obj). Keep in mind that .mtl file and correct texture files have to be in the same folder. You can play around with model and light transform in this panel.");
		ImGui::PopTextWrapPos();
		ImGui::PopStyleVar();

		bool modelLoadRequested = false;
		std::string modelPath = "";
		SettingsPanel::DrawModelBrowser(modelLoadRequested, modelPath);

		if (modelLoadRequested)
		{
			Model::Load(modelPath);
			m_ModelInfo = Model::GetModelInfo();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 5 });
		ImGui::Text("Model settings:");
		ImGui::PopStyleVar();

		SettingsPanel::DrawVec3Control("Position (M)", m_ModelPos);

		glm::vec3 rotation = glm::degrees(m_ModelRotation);
		SettingsPanel::DrawVec3Control("Rotation (M)", rotation);
		m_ModelRotation = glm::radians(rotation);
		SettingsPanel::DrawVec3Control("Scale (M)", m_ModelScale, 1.0f);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 20 });
		ImGui::Text("");
		ImGui::PopStyleVar();

		// Light settings
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 5 });
		ImGui::Text("Light settings:");
		ImGui::PopStyleVar();

		SettingsPanel::DrawVec3Control("Position (L)", m_LightPos);
		SettingsPanel::DrawRGBControl("Color", m_LightColor);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 5 });
		ImGui::Text("");
		ImGui::PopStyleVar();

		SettingsPanel::DrawFloatControl("Ambient", m_LightAmbient);
		SettingsPanel::DrawFloatControl("Diffuse", m_LightDiffuse);
		SettingsPanel::DrawFloatControl("Specular", m_LightSpecular);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 20 });
		ImGui::Text("");
		ImGui::PopStyleVar();

		// Model info
		ImGui::Text("Meshes: %d", m_ModelInfo.MeshCount);
		ImGui::Text("Vertices: %d", m_ModelInfo.VerticeCount);

		ImGui::Text("Textures loaded (%d):", m_ModelInfo.TextureCount.size());
		for (auto& texture : m_ModelInfo.TextureCount)
		{
			ImGui::Text(texture.c_str());
		}

		ImGui::End();

		// Viewport
		ImGui::Begin("Viewport", (bool*)true, subWindowFlags);

		ImVec2 size = ImGui::GetContentRegionAvail();
		
		// Resizing
		static bool firstTime = true;
		if (m_ViewportSize != *((glm::vec2*)&size))
		{
			if (firstTime)
			{
				m_ViewportSize = { size.x, size.y };
				firstTime = false;
			}
			else
			{
				m_Framebuffer->Resize((uint32_t)size.x, (uint32_t)size.y);
				m_ViewportSize = { size.x, size.y };
			}
		}

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		// End main window
		ImGui::End();
		ImGui::PopStyleVar();
	}
private:
	glm::vec2 m_ViewportSize;

	std::unique_ptr<Framebuffer> m_Framebuffer;

	ModelInfo m_ModelInfo;
	glm::vec3 m_ModelPos = glm::vec3(0.0f);
	glm::vec3 m_ModelRotation = glm::vec3(0.0f);
	glm::vec3 m_ModelScale = glm::vec3(1.0f);

	glm::vec3 m_LightPos = glm::vec3(0.0f);
	glm::vec3 m_LightColor = glm::vec3(255.0f);
	float m_LightAmbient = 0.2f;
	float m_LightDiffuse = 0.5f;
	float m_LightSpecular = 1.0f;
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