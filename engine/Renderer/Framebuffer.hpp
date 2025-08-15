// engine/Renderer/Framebuffer.hpp
#pragma once
#include <cstdint>

namespace Groove {
    class Framebuffer {
    public:
        static uint32_t Create(uint32_t width, uint32_t height);
        static void Bind(uint32_t fbo);
        static void Unbind();
        static void Resize(uint32_t fbo, uint32_t width, uint32_t height);
        static uint32_t GetColorAttachment(uint32_t fbo);
    };
}
