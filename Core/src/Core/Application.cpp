#include "cpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Core {

	// Assign instance to nullptr
	Application* Application::s_Instance = nullptr;

	// Constructor
	Application::Application(const ApplicationProperties& props)
	{
		// Handle application initialization
		if (!s_Instance)
		{
			// Initialize log
			Log::Init();
			LOG_INFO("Application initialized!");
		}

		s_Instance = this;

		m_Window = Window::Create({ props.Label, props.Width, props.Height});

		//m_Gui = new GuiLayer();
		//PushLayer(m_Gui);

		// Triangle test
		Shader::LoadShaders();

		m_VertexArray = VertexArray::Create();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,		/**/	0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,		/**/	1.0f, 0.0f,
			0.5f, 0.5f, 0.0f,		/**/	1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f,		/**/	0.0f, 1.0f
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout =
		{
			{ "a_Position", ShaderDataType::Float3},
			{ "a_TextureCoords", ShaderDataType::Float2}
		};

		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_IndexBuffer = IndexBuffer::Create(indices, 6);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Texture = Texture::Create("assets/textures/brick.jpg");

		Shader::Bind();
		Shader::UploadUniformInt("u_Texture", 0);
	}

	Application::~Application()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Clear();

			// Check for window related events
			Input::IsWindowBeingClosed([&]()
			{
				m_Running = false;
			});

			// Update layers
			for (auto& layer : m_Layers)
			{
				layer->OnUpdate();
			}

			//Render GUI
			//m_Gui->Begin();
			//for (auto& layer : m_Layers)
			//{
			//	layer->OnGuiRender();
			//}
			//m_Gui->End();

			// Update the window

			Shader::Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Window->Update();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}