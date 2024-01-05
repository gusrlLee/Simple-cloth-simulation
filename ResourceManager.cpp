#include "ResourceManager.h"

void ResourceManager::loadShader(const char* name, const char* vshader_path, const char* fshader_path)
{
    std::string vshader_code;
    std::string fshader_code;
    std::ifstream vshader_file;
    std::ifstream fshader_file;

    vshader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fshader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vshader_file.open(vshader_path);
        fshader_file.open(fshader_path);

        std::stringstream vshader_stream, fshader_stream;
        vshader_stream << vshader_file.rdbuf();
        fshader_stream << fshader_file.rdbuf();

        vshader_file.close();
        fshader_file.close();

        vshader_code = vshader_stream.str();
        fshader_code = fshader_stream.str();
    } 
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    Shader shader;
    shader.compile(vshader_code.c_str(), fshader_code.c_str());
    shaders.insert({name, shader});
}

Shader ResourceManager::getShader(std::string name)
{
    return shaders[name];
}