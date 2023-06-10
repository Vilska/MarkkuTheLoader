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

		//m_TestModel = std::make_unique<Model>("assets/models/backpack.obj");

		//m_Gui = new GuiLayer();
		//PushLayer(m_Gui);

		// Test
		Shader::LoadShaders({"Model", "Light"});

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		m_VertexArray = VertexArray::Create();

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout =
		{
			{ "a_Position", ShaderDataType::Float3},
			{ "a_Normal", ShaderDataType::Float3 }
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Light
		m_LightVAO = VertexArray::Create();

		m_LightVBO = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout lightLayout =
		{
			{ "a_Position", ShaderDataType::Float3},
			{ "a_Normal", ShaderDataType::Float3 }
		};
		m_LightVBO->SetLayout(lightLayout);

		m_LightVAO->AddVertexBuffer(m_LightVBO);


		//uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		//m_IndexBuffer = IndexBuffer::Create(indices, 6);
		//m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		//m_Texture = Texture::Create("assets/textures/box.jpg");
		//m_OverlayTexture = Texture::Create("assets/textures/stop.png");
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

			//Shader::Bind();
			//Shader::UploadUniformMat4("ViewProjection", m_Camera->GetViewProjectionMatrix());

			// Model cube
			Shader::Bind("Model");

			glm::vec3 lightPos = { 1.2f, 2.0f, 2.0f };
			lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
			lightPos.y = (sin(glfwGetTime()) / 1.0f) * 2.0f;

			Shader::UploadUniform("Model", "ViewProjection", m_Camera->GetViewProjectionMatrix());
			Shader::UploadUniform("Model", "Transform", glm::mat4(1.0f));
			Shader::UploadUniform("Model", "LightPos", lightPos);
			Shader::UploadUniform("Model", "LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			Shader::UploadUniform("Model", "ViewPos", m_Camera->GetPosition());

			m_VertexArray->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Light cube
			Shader::Bind("Light");
			Shader::UploadUniform("Light", "ViewProjection", m_Camera->GetViewProjectionMatrix());

			glm::mat4 transform(1.0f);
			transform = glm::translate(transform, lightPos);
			transform = glm::scale(transform, glm::vec3(0.2f));
			Shader::UploadUniform("Light", "Transform", transform);

			m_LightVAO->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Test model
			//m_TestModel->Draw();

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