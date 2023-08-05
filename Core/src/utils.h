#pragma once
#include <string>


const std::string ReadFile(const std::string& filepath);

void SetRandomSeed();

float RandomFloat(float min, float max, unsigned int precision=3);