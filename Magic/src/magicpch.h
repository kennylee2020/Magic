#pragma once
#include "Magic/Core/Log.h"

#ifdef NDEBUG
	#define ASSERT(expression) ((void)0)
#else
	#define ASSERT(expression) assert(expression)
#endif

