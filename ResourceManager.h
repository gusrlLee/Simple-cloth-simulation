#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class ResourceManager 
{
    public:
        ResourceManager() {}

        void loadShader(const char* name, const char* vshader_path, const char* fshader_path);
        Shader getShader(std::string name);

        void loadModel(const char* name, const char* model_path);

    private:
        // TODO: need to implement Resource map vector 
        // Shader file 
        std::map<std::string, Shader> shaders;

};
