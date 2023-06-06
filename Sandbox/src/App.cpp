#include <memory>

#include "Core.h"

using namespace Core;

class App : public Application
{
public:
	App()
		: Application()
	{
		LOG_INFO("App is constructed!");
	}
};

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>();
	app->Run();
}