#pragma once
#define BIT(shift) 1 << shift

#define BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)

#ifdef NDEBUG
#define ASSERT(_EXPR) ((void)0)
#else
#define ASSERT(_EXPR) assert(_EXPR)
#endif
