#pragma once
#include "core.h"
#include "framework.h"

class Timestep {
private:
	float _lastTimeFrame;
	std::shared_ptr<core::Platform> platform;
public:
	float deltaTime;

	Timestep() : deltaTime(0), _lastTimeFrame(0), platform(Framework::GetInstance()->Platform()) {}

	float GetSeconds() {
		return deltaTime;
	}

	float GetMilliseconds() {
		return deltaTime * 1000.0f;
	}

	void Update() {
		float time = platform->GetTime();
		deltaTime = time - _lastTimeFrame;
		_lastTimeFrame = time;
	}
};