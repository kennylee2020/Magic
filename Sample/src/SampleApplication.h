#pragma once
#include "Magic.h"

namespace Sample {
	class SampleApplication : public Magic::Application
	{
	public:
		SampleApplication(const Magic::Application::ApplicationDesc desc);
		~SampleApplication();
	private:
	};
}