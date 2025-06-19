#pragma once  

namespace Groove {  

    class Renderer {  
    public:  
        // Call once after GL and window init  
        static void Init();  

        // Draw a cube with transform and camera  
        static void DrawCube(const class Transform& t, const class Camera& cam);  

        // Set the camera perspective with aspect ratio
        static void SetCameraPerspective(class Camera& cam, float aspect);

        // Call on shutdown if needed  
        static void Shutdown();  

    private:  
        static unsigned int s_VAO, s_VBO, s_IBO;
        static class Shader* s_Shader;  
    };  

}
