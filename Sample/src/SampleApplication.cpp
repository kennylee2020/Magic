#include "SampleApplication.h"
#include "Magic/Core/EntryPoint.h"

namespace Sample {
	SampleApplication::SampleApplication()
	{
		Magic::MAG_INFO("Sample start!");
	}

	SampleApplication::~SampleApplication()
	{
	}
}

Magic::Application* Magic::createApplication() {
	return new Sample::SampleApplication();
}