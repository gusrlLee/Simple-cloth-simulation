#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Config.h"
#include "ResourceManager.h"
#include "Sphere.h"
#include "Camera.h"
#include "Cloth.h"

#include <iostream>
#include <string>

class Simulator 
{
    public:
        Simulator() {}

        void setUp();
        void run();
        void exit();

    private:
        void processInput(GLFWwindow* window);

        bool m_status = false;
        GLFWwindow* m_window;

        ResourceManager* m_resource_manager;
        Sphere* m_sphere;
        Cloth* m_cloth;
        Camera* m_cam;
};