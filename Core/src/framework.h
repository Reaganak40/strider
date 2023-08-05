#pragma once

#include "core.h"
#include "platform.h"
#include <memory>
class Framework {
public:
	static Framework* GetInstance();

	Framework(const Framework&) = delete;
	Framework(Framework&&) = delete;
	Framework& operator=(const Framework&) = delete;
	Framework& operator=(Framework&&) = delete;
private:
	Framework(FrameworkType type = USING_NONE);
	~Framework();

	std::shared_ptr<core::Platform> m_platform;
	static Framework* instancePtr;
public:
	inline const std::shared_ptr<core::Platform>& Platform() { return m_platform; }
};

