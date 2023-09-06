#pragma once
namespace Magic {
	enum class FramebufferTextureFormat {
		None = 0,

		//Color
		RGBA8,
		RED_INTEGER,
		//Depth & Stencil
		DEPTH24STENCIL8,

		DepthDefault = DEPTH24STENCIL8,
	};

	struct FramebufferTextureDescriptor {
		FramebufferTextureDescriptor() = default;
		FramebufferTextureDescriptor(FramebufferTextureFormat format) : format(format) {}
		FramebufferTextureFormat format = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentDescriptor {
		FramebufferAttachmentDescriptor() = default;
		FramebufferAttachmentDescriptor(std::initializer_list<FramebufferTextureDescriptor> attachments) : attachments(attachments){}
		std::vector<FramebufferTextureDescriptor> attachments;
	};

	struct FramebufferDescriptor
	{
		uint32_t width = 0,height = 0;
		FramebufferAttachmentDescriptor attachments;
		uint32_t samples = 1;
		bool swapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
		virtual uint32_t GetColorAttachmentRendererID(uint32_t attachmentIndex = 0) const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	public:
		static Ref<Framebuffer> Create(const FramebufferDescriptor& desc);
	};
}