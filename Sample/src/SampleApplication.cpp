#include "SampleApplication.h"
#include "SampleLayer.h"

#include "Magic/Core/EntryPoint.h"

namespace Sample {
	SampleApplication::SampleApplication()
	{
		Magic::MAG_INFO("Sample start!");
		PushLayer(new Sample::SampleLayer());
	}

	SampleApplication::~SampleApplication()
	{
	}
}

Magic::Application* Magic::CreateApplication() {
	return new Sample::SampleApplication();
}