#pragma once
#include <string>

namespace Magic {
	class Shader
	{
	public:
		enum class ShaderType{
			None = 0,Vertex,Fragment,
		};
	public:
		Shader() = default;
		~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		static std::shared_ptr<Shader> Create(std::string filePath);
	};
}
