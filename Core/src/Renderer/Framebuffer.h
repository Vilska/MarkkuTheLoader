#pragma once

#include <memory>

namespace Core {

	struct FramebufferData
	{
		uint32_t Width, Height;
		uint32_t Samples;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferData& data);
		~Framebuffer();

		void Invalidate();

		void Bind();
		void Unbind();

		void Resize(uint32_t width, uint32_t height);

		inline uint32_t GetColorAttachmentRendererID() { return m_RendererID; }
		inline const FramebufferData& GetData() { return m_Data; }

		static std::unique_ptr<Framebuffer> Create(const FramebufferData& data);
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferData m_Data;
	};

}
