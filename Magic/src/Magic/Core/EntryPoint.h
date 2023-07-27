#include "magicpch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	Magic::Log::Init();

	Magic::Application* app = Magic::CreateApplication();
	app->run();
	delete app;
	return 0;
}
