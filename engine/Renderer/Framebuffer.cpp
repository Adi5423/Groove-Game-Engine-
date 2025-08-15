// engine/Renderer/Framebuffer.cpp
#include "Framebuffer.hpp"
#include <glad/glad.h>

namespace Groove {

    static uint32_t s_ColorAttachment = 0;

    uint32_t Framebuffer::Create(uint32_t width, uint32_t height) {
        uint32_t fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        // Create texture
        glGenTextures(1, &s_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, s_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s_ColorAttachment, 0);

        // Create depth buffer
        uint32_t rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            return 0;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return fbo;
    }

    void Framebuffer::Bind(uint32_t fbo) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }

    void Framebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Resize(uint32_t fbo, uint32_t width, uint32_t height) {
        Bind(fbo);
        glBindTexture(GL_TEXTURE_2D, s_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    uint32_t Framebuffer::GetColorAttachment(uint32_t fbo) {
        return s_ColorAttachment;
    }
}
