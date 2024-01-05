#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.h"
#include "Config.h"

#include <vector>

class Cloth
{
    public:
        Cloth() = default;
        Cloth(int width, int height, float spacing, int startX, int startY, int startZ);
        ~Cloth();

        void update(float delta_time);
	    void draw(Shader &shader);
        void checkCollision(glm::vec3 &p);

    private:
        glm::vec3 gravity = glm::vec3(0.0f, -G, 0.0f);
        glm::vec3 force = glm::vec3(0.0f, 5.5f, 0.0f);
        float m_spacing;
        float elasticity = 10.0f;
        float particle_mass = 10000.0f;
        int m_stick_cnt;


        unsigned int VAO;
        unsigned int stick_VAO;
        std::vector<std::pair<int, int>> sticks;
        
        int m_point_cnt;
        glm::vec3* m_curr_points;
        glm::vec3* m_prev_points;
        glm::vec3* m_stick_points;
};