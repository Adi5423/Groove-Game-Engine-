#pragma once
#include <cstdint>

namespace Groove {

    class Framebuffer {
    public:
        Framebuffer() = default;
        ~Framebuffer();

        // Create framebuffer with color texture + depth RBO
        bool Create(int width, int height);

        // Resize (recreates attachments)
        void Resize(int width, int height);

        // Bind / Unbind
        void Bind() const;
        static void Unbind();

        // Get GL texture id for ImGui::Image()
        uint32_t GetColorTexture() const { return m_ColorTexture; }

        // Get dimensions
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

    private:
        void Destroy();

        uint32_t m_FBO = 0;
        uint32_t m_ColorTexture = 0;
        uint32_t m_RBO = 0;
        int m_Width = 0;
        int m_Height = 0;
    };

} // namespace Groove
