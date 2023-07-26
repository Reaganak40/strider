#pragma once
#include <iostream>
#include "core.h"

typedef unsigned int ShaderID;

unsigned int CompileShader(unsigned int type, const std::string& source);

ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

inline void BindShader(ShaderID program) { glUseProgram(program); }
