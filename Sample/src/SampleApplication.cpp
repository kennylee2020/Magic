#include "SampleApplication.h"

namespace Sample {
	SampleApplication::SampleApplication()
	{
	}

	SampleApplication::~SampleApplication()
	{
	}
}

int main()
{
	Sample::SampleApplication app;
	Magic::MAG_INFO("Sample start!");
	app.Run();
}
