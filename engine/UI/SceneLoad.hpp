#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace Groove {

    struct Transform;
    class Camera;
    class Framebuffer;

    class SceneLoad {
    public:
        static void Init();
        static void Shutdown();

        // call per-frame to update internal logic
        static void Update(float dt);

        // Render the scene into the framebuffer
        static void RenderSceneToFramebuffer();

        // Called during UI pass to draw the ImGui panel and the framebuffer texture
        static void OnImGuiRender();

    private:
        static std::unique_ptr<Camera> s_Camera;
        static std::unique_ptr<Framebuffer> s_Framebuffer;
        static std::vector<Transform> s_Transforms;

        static int s_ViewportWidth;
        static int s_ViewportHeight;
        static bool s_ViewportFocused;
        static bool s_ViewportHovered;
    };

} // namespace Groove
