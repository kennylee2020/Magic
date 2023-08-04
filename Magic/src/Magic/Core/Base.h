#pragma once
#include <memory>

#define BIT(shift) 1 << shift

#define BIND_EVENT_CALLBACK(callback) std::bind(&callback, this, std::placeholders::_1)

#ifdef NDEBUG
#define ASSERT(_EXPR) ((void)0)
#else
#define ASSERT(_EXPR) assert(_EXPR)
#endif

namespace Magic {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...)
	};

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	};
}
