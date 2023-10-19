#include <iostream>
#include <memory>
#include "EgorkaEngineCore/Application.hpp"

class MyApp : public EgorkaEngine::Application
{
	virtual void on_update() override
	{
		//std::cout << "frame" << frame++;
	}

	int frame = 0;
};

int main()
{
	auto myApp = std::make_unique<MyApp>();

	int returnCode = myApp->start(1024, 768, "a");

	std::cin.get();

	return returnCode;
}