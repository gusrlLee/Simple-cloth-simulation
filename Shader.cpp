#include "Shader.h"

Shader &Shader::use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::compile(const char* vshader_code, const char* fshader_code)
{
    unsigned int vertex, fragment;
    // create and compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vshader_code, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fshader_code, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char info[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, info);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << info << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, info);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << info << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

