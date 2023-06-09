#include "cpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "Time.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_Camera = Camera::Create(45.0f, props.Width / props.Height);

		//m_Gui = new GuiLayer();
		//PushLayer(m_Gui);

		// Test
		Shader::LoadShaders();

		m_VertexArray = VertexArray::Create();

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout =
		{
			{ "a_Position", ShaderDataType::Float3},
			{ "a_TextureCoords", ShaderDataType::Float2}
		};

		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		//m_IndexBuffer = IndexBuffer::Create(indices, 6);
		//m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Texture = Texture::Create("assets/textures/box.jpg");
		m_OverlayTexture = Texture::Create("assets/textures/stop.png");

		Shader::Bind();
		Shader::UploadUniformInt("u_Texture1", 0);
		Shader::UploadUniformInt("u_Texture2", 1);
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
			m_DeltaTime = DeltaTime::Calculate(glfwGetTime());

			m_Window->Clear();

			m_Camera->Update(m_DeltaTime);

			// Update layers
			for (auto& layer : m_Layers)
			{
				layer->Update();
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
			m_Texture->Bind(0);
			m_OverlayTexture->Bind(1);

			// 3D test cubes

			glm::vec3 cubePositions[] =
			{
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};

			Shader::UploadUniformMat4("ViewProjection", m_Camera->GetViewProjectionMatrix());

			m_VertexArray->Bind();
			for (int i = 0; i < 10; i++)
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i * glfwGetTime();
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3, 0.5));
				Shader::UploadUniformMat4("Model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			m_Window->Update();

		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_Camera->OnEvent(event);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}