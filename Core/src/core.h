#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define DYNAMIC_BUFFER_DEFAULT_LIMIT 1000
typedef int EntityID;
typedef const char* SceneID;
