#pragma once
#include <iostream>
#include "core.h"

#include <glm/glm.hpp>

typedef unsigned int ShaderID;
typedef int UniformVariable;

unsigned int CompileShader(unsigned int type, const std::string& source);

ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

inline void BindShader(ShaderID program) { glUseProgram(program); }

UniformVariable GetUniformVariable(ShaderID id, const std::string& name);

void SetUniform4f(UniformVariable uv, float v0, float v1, float v2, float v3);
void SetUniform1i(UniformVariable uv, int v0);
void SetUniformMat4f(UniformVariable uv, glm::mat4 matrix);