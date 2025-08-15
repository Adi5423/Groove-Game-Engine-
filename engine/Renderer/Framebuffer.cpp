#include "Framebuffer.hpp"
#include <glad/glad.h>
#include <iostream>

namespace Groove {

    Framebuffer::~Framebuffer() {
        Destroy();
    }

    bool Framebuffer::Create(int width, int height) {
        Destroy();

        if (width <= 0 || height <= 0) return false;

        m_Width = width;
        m_Height = height;

        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // Create color texture
        glGenTextures(1, &m_ColorTexture);
        glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // or GL_NEAREST for crisp
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // clamp to edge to prevent border artifacts
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTexture, 0);

        // Create renderbuffer for depth + stencil
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "[Framebuffer] Framebuffer not complete!\n";
            // cleanup partially created objects
            Destroy();
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return false;
        }

        // Unbind
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return true;
    }

    void Framebuffer::Resize(int width, int height) {
        if (width == m_Width && height == m_Height) return;
        Create(width, height);
    }

    void Framebuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    }

    void Framebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Destroy() {
        if (m_RBO) { glDeleteRenderbuffers(1, &m_RBO); m_RBO = 0; }
        if (m_ColorTexture) { glDeleteTextures(1, &m_ColorTexture); m_ColorTexture = 0; }
        if (m_FBO) { glDeleteFramebuffers(1, &m_FBO); m_FBO = 0; }
        m_Width = m_Height = 0;
    }

} // namespace Groove
