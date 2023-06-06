#pragma once

namespace Core {

	//struct ApplicationProperties
	//{
	//	const std::string Label = "Default";
	//	uint16_t Width = 1280;
	//	uint16_t Height = 720;
	//};

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
	private:
		bool m_Running = true;

		static Application* s_Instance;
	};
}
