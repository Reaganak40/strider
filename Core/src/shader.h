#pragma once
#include <iostream>

int CompileShader(unsigned int type, const std::string& source);

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

const std::string LoadShader(const std::string& filepath);