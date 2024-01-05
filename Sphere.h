#pragma once 

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.h"
#include "Config.h"

#include <iostream>

class Sphere {
    public:
        Sphere();
        std::vector<float> data;
        void draw(Shader &shader);

    private:
        unsigned int m_VAO;
        unsigned int m_index_count;
};
