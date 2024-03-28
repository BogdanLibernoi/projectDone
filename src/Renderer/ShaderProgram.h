#ifndef SHADERPROGRAM_H

#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef std::string str;


class ShaderProgram
{
public:
    unsigned int ShaderProgramID;

    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        str _vertexShaderCode;
        str _fragmentShaderCode;
        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        vertexShaderFile.exceptions (std::ifstream::failbit | std::fstream::badbit);
        fragmentShaderFile.exceptions (std::ifstream::failbit | std::fstream::badbit);
        try
        {
            vertexShaderFile.open(vertexShaderPath);
            fragmentShaderFile.open(fragmentShaderPath);
            std::stringstream vertexShaderStream, fragmentShaderStream;

            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            _vertexShaderCode = vertexShaderStream.str();
            _fragmentShaderCode = fragmentShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout<< "Error while reading shaderFile\n";   
        }
        const char* vertexShaderCode = _vertexShaderCode.c_str();
        const char* fragmentShaderCode = _fragmentShaderCode.c_str();



        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {   
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "VertexShader compilation failed\n" << infoLog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {   
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "fragmentShader compilation failed\n" << infoLog << std::endl;
        }


        
        ShaderProgramID = glCreateProgram();
        glAttachShader(ShaderProgramID, vertex);
        glAttachShader(ShaderProgramID, fragment);
        glLinkProgram(ShaderProgramID);

        glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
            std::cout << "Error while ShaderProgram linking\n" << infoLog << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use(){
        glUseProgram(ShaderProgramID);
    }

    void SetBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), (int)value);
    }
    void SetInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
    }
    void SetFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0] );
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y); 
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z); 
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) const
    { 
        glUniform4f(glGetUniformLocation(ShaderProgramID, name.c_str()), x, y, z, w); 
    }


    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};

#endif