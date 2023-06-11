#pragma once

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"

#include "Event/Event.h"
#include "Event/WindowEvent.h"

#include "Model/Model.h"

namespace Core {

	struct ApplicationProperties
	{
		const std::string Label;
		uint16_t Width;
		uint16_t Height;

		ApplicationProperties(const std::string& label = "Default", uint16_t width = 1280, uint16_t height = 720)
			: Label(label), Width(width), Height(height) {}
	};

	class Application
	{
	public:
		Application(const ApplicationProperties& props);
		~Application();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& event) { m_Running = false; return m_Running; }
	private:
		bool m_Running = true;
		float m_DeltaTime = 0;

		// Buffers & vertex arrays
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_LightVBO;
		std::shared_ptr<IndexBuffer> m_LightIBO;
		std::shared_ptr<VertexArray> m_LightVAO;

		// Subclass pointers
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Texture> m_DiffuseMap;
		std::unique_ptr<Texture> m_SpecularMap;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Model> m_TestModel;
		//GuiLayer* m_Gui;

		// Vectors
		std::vector<Layer*> m_Layers;

		// Instance
		static Application* s_Instance;
	};
}
