#pragma once

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
		MAG_CORE_ERROR("Unknown ShaderDataType {0}", (int)type);
		return 0;
	}

	static int shaderDataType2Dimension(const ShaderDataType type) {
		switch (type)
		{
		case Magic::ShaderDataType::None:	return 0;
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
		MAG_CORE_ERROR("Unknown ShaderDataType {0}", (int)type);
		return 0;
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
		virtual ~Buffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetBufferData(const void* data, uint32_t size) = 0;

		static Ref<Buffer> Create(const BufferLayout& layout);
	protected:
		Buffer() = default;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		virtual void SetBufferData(const uint32_t* data, uint32_t count) = 0;

		static Ref<IndexBuffer> Create();
	};

	class UniformBuffer 
	{
	public:
		virtual ~UniformBuffer(){}
		virtual void SetBufferData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static Ref<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};
}
