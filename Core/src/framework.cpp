#include "framework.h"
#include <opengl/platformGL.h>

Framework* Framework::instancePtr = nullptr;

Framework* Framework::GetInstance()
{
	if (!instancePtr) {
		instancePtr = new Framework((FrameworkType)SR_PLATFORM_FRAMEWORK);
	}

	return instancePtr;

}

Framework::Framework(FrameworkType type) {

	switch (type) {
	case USING_GL:
		m_platform = std::make_shared<core::PlatformGL>();
		break;
	default:
		m_platform = nullptr;
	}
}
Framework::~Framework()
{
}
