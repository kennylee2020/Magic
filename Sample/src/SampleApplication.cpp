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
	app.Run();
}