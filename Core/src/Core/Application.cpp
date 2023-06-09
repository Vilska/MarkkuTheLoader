#include "cpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

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

			glm::mat4 view(1.0f);
			glm::mat4 projection(1.0f);
			projection = glm::perspective(glm::radians(45.0f), (float)GetWindow().GetWidth() / (float)GetWindow().GetHeight(), 0.1f, 100.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			Shader::UploadUniformMat4("projection", projection);
			Shader::UploadUniformMat4("view", view);

			m_VertexArray->Bind();
			for (int i = 0; i < 10; i++)
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i * glfwGetTime();
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3, 0.5));
				Shader::UploadUniformMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			m_Window->Update();

		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}