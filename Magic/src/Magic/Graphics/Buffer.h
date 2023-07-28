#pragma once
#include "magicpch.h"

namespace Magic {
	enum class ShaderDataType {
		None = 0, Bool, Int, Int2, Int3, Int4, Float, Float2, Float3, Float4
	};

	static int shaderDataType2Size(const ShaderDataType type) {
		switch (type)
		{
		case Magic::ShaderDataType::None:	return 0;
		case Magic::ShaderDataType::Bool:	return 1;
		case Magic::ShaderDataType::Int:	return 4;
		case Magic::ShaderDataType::Int2:	return 4 * 2;
		case Magic::ShaderDataType::Int3:	return 4 * 3;
		case Magic::ShaderDataType::Int4:	return 4 * 4;
		case Magic::ShaderDataType::Float:	return 4;
		case Magic::ShaderDataType::Float2:	return 4 * 2;
		case Magic::ShaderDataType::Float3:	return 4 * 3;
		case Magic::ShaderDataType::Float4:	return 4 * 4;
		}
		MAG_ERROR_CORE("Unknown ShaderDataType {0}", 0);
	}

	static int shaderDataType2Dimension(const ShaderDataType type) {
		switch (type)
		{
		case Magic::ShaderDataType::None:	return 1;
		case Magic::ShaderDataType::Bool:	return 1;
		case Magic::ShaderDataType::Int:	return 1;
		case Magic::ShaderDataType::Int2:	return 2;
		case Magic::ShaderDataType::Int3:	return 3;
		case Magic::ShaderDataType::Int4:	return 4;
		case Magic::ShaderDataType::Float:	return 1;
		case Magic::ShaderDataType::Float2:	return 2;
		case Magic::ShaderDataType::Float3:	return 3;
		case Magic::ShaderDataType::Float4:	return 4;
		}
		MAG_ERROR_CORE("Unknown ShaderDataType {0}", 0);
	}

	class BufferLayout {
	public:
		class LayoutRow
		{
		public:
			std::string name;
			ShaderDataType type;
			int normalized;
			int size;
			int offset;
			int dimension;
		public:
			LayoutRow() = default;
			LayoutRow(const std::string& name, ShaderDataType type,int normalized) 
				: name(name), type(type),size(shaderDataType2Size(type)), dimension(shaderDataType2Dimension(type)), normalized(normalized), offset(0){}
		};
	public:
		BufferLayout(std::initializer_list<LayoutRow> elements) : m_Layouts(elements){ calculateOffsetAndStride();}

		inline int getStride() const { return m_Stride;}
		inline const std::vector<LayoutRow>& getLayouts() const { return m_Layouts; }
	private:
		int m_Stride;
		std::vector<LayoutRow> m_Layouts;
	private:
		void calculateOffsetAndStride() {
			int offset = 0, stride = 0;
			for (LayoutRow& row : m_Layouts) {
				row.offset = offset;
				offset += row.size;
				stride += row.size;
			}
			m_Stride = stride;
		}
	};

	class Buffer
	{
	public:
		Buffer(const BufferLayout& layout) {};
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setBufferData(unsigned int size, const void* data) = 0;

		static std::shared_ptr<Buffer> create(const BufferLayout& layout);
	protected:
		Buffer() = default;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual int getCount() const = 0;
		virtual void setBufferData(unsigned int count, const unsigned int* data) = 0;

		static std::shared_ptr<IndexBuffer> create();
	};
}
