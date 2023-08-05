#include "messageManager.h"

#include "renderer.h"
#include "framework.h"
#include "entityManager.h"

MessageManager* MessageManager::mmPtr = nullptr;

MessageManager* MessageManager::GetInstance()
{
	if (mmPtr == nullptr) {
		mmPtr = new MessageManager;
	}
	return mmPtr;
}

MessageManager::MessageManager()
	: m_framework(Framework::GetInstance()), m_renderer(nullptr), m_entity_manager(nullptr)
{

}

MessageManager::~MessageManager()
{
}

void MessageManager::SetRenderer(std::shared_ptr<Renderer> nRenderer)
{
	m_renderer = nRenderer;
}

void MessageManager::SetEntityManager(EntityManager* nEntityManager)
{
	m_entity_manager = nEntityManager;
}

MessageResponse MessageManager::SendEventToEM(Request nEvent)
{
	return 0;
}

MessageResponse MessageManager::QueryFramework(unsigned int message)
{
	MessageResponse response = 0;
	if (message ^ WindowOpen) {
		if (m_framework->Platform()->IsOpen()) {
			response |= WindowOpen;
		}
	}

	return response;
}

void MessageManager::SendRequestToRenderer(Request& request)
{
	m_renderer->OnRequest(request);
}

void MessageManager::SendRequestToEntityManager(Request& request)
{
	m_entity_manager->OnRequest(request);
}
