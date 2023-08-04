#include "SampleApplication.h"
#include "SampleLayer.h"

#include "Magic/Core/EntryPoint.h"

namespace Sample {
	SampleApplication::SampleApplication(const Magic::Application::ApplicationDesc desc) : Magic::Application::Application(desc)
	{
		Magic::MAG_INFO("Sample start!");
		PushLayer(new Sample::SampleLayer());
	}

	SampleApplication::~SampleApplication()
	{
	}
}

Magic::Application* Magic::CreateApplication() {
	Magic::Application::ApplicationDesc desc;
	return new Sample::SampleApplication(desc);
}