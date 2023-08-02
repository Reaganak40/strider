#pragma once
#include "core.h"

class Timestep {
private:
	float _lastTimeFrame;
public:
	float deltaTime;

	Timestep() : deltaTime(0), _lastTimeFrame(0) {}

	float GetSeconds() {
		return deltaTime;
	}

	float GetMilliseconds() {
		return deltaTime * 1000.0f;
	}

	void Update() {
		float time = (float)glfwGetTime();
		deltaTime = time - _lastTimeFrame;
		_lastTimeFrame = time;
	}
};