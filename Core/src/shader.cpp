#include <fstream>
#include <string>

#include "error.h"
#include "shader.h"

unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: ERROR HANDLING
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n";
        std::cout << message << std::endl;

        delete[] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    ShaderID program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glCall(glAttachShader(program, vs));
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glCall(glDeleteShader(fs));

    return program;
}

UniformVariable GetUniformVariable(ShaderID id, const std::string& name) {
    UniformVariable location;
    glCall(location = glGetUniformLocation(id, name.c_str()));
    if (location < 0) {
        std::cout << "Warning: UniformVariable [" << name << "] does not exist.\n";
    }

    return location;
}

void SetUniform4f(UniformVariable uv, float v0, float v1, float v2, float v3) {
    glCall(glUniform4f(uv, v0, v1, v2, v3));
}

void SetUniform1i(UniformVariable uv, int v0) {
    glCall(glUniform1i(uv, v0));
}

void SetUniformMat4f(UniformVariable uv, glm::mat4 matrix)
{
    glCall(glUniformMatrix4fv(uv, 1, GL_FALSE, &matrix[0][0]));
}
