#pragma once

namespace Groove {

    class Renderer {
    public:
        // Call once after GL and window init
        static void Init();

        // Draw a simple test triangle
        static void DrawTriangle();

        // Call on shutdown if needed
        static void Shutdown();

    private:
        static unsigned int s_VAO;
        static unsigned int s_VBO;
        static class Shader* s_Shader;
    };

}
