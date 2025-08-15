#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace Groove {

    class Camera;
    struct Transform;

    class SceneLoad {
    public:
        static void Init();
        static void Shutdown();

        static void Update(float dt);
        static void OnImGuiRender(); // Called from PrimaryWindow "3D Scene" tab

    private:
        static std::unique_ptr<Camera> s_Camera;
        static std::vector<Transform> s_Transforms;
        static unsigned int s_Framebuffer; // for viewport rendering
        static int s_ViewportWidth;
        static int s_ViewportHeight;
        static bool s_ViewportFocused;
        static bool s_ViewportHovered;

        static void ResizeFramebuffer(int width, int height);
        static void RenderScene();
    };

} // namespace Groove
