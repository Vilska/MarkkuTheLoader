#pragma once

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"

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

		void PushLayer(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool m_Running = true;

		// Buffers & vertex arrays
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		// Subclass pointers
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Texture> m_Texture;
		//GuiLayer* m_Gui;

		// Vectors
		std::vector<Layer*> m_Layers;

		// Instance
		static Application* s_Instance;
	};
}
