#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"

#include <vector>
#include <algorithm>
#include <iostream>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh
{
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

    private:
        void setUpMesh();
        unsigned int VAO, VBO, EBO;
};