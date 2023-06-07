#include <memory>

#include "Core.h"

using namespace Core;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() = default;
	virtual ~ExampleLayer() = default;

	virtual void OnGuiRender() override
	{
		// This is not working for some reason
		ImGui::Begin("Test");
		ImGui::Text("This is a test window!");
		ImGui::End();
	}
};

class App : public Application
{
public:
	App()
		: Application()
	{
		PushLayer(new ExampleLayer());
	}
};

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
}