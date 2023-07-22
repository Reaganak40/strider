#include <fstream>
#include <string>

#include "core.h"

int CompileShader(unsigned int type, const std::string& source) {
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

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

const std::string LoadShader(const std::string& filepath) {
    std::ifstream sFilestream(filepath);

    std::string sFileBuffer;
    if (sFilestream.is_open()) { // always check whether the file is open

        while (sFilestream) {
            std::string line;
            std::getline(sFilestream, line);
            sFileBuffer += line + '\n';
        }
    }
    else {
        std::cout << "Error: Could not open '" << filepath << "'\n";
    }

    sFilestream.close();
    return sFileBuffer;
}