#pragma once
#include <iostream>
#include <string>
#define ASSERT(x) if (!(x)) __debugbreak();

#define glCall(x) glClearError(); x; ASSERT(glLogError(#x, __FILE__, __LINE__))

void glClearError();
bool glLogError(const char* function, const char* filename, int line);
std::string glErrorContext(unsigned int error);
