#pragma once

#include <memory>
#include "request.h"

class Framework;
class Renderer;
class EntityManager;

enum frameworkMessage {
	WindowOpen = 1,
};

typedef unsigned int MessageResponse;

class MessageManager {
public:
	static MessageManager* GetInstance();
private:
	MessageManager();
	~MessageManager();
	static MessageManager* mmPtr;

	Framework* m_framework;
	std::shared_ptr<Renderer> m_renderer;
	EntityManager* m_entity_manager;
	

public:

	void SetRenderer(std::shared_ptr<Renderer> nRenderer);
	void SetEntityManager(EntityManager* nEntityManager);

	template<typename Receiver>
	void SendRequest(Request& request) { }

	template<>
	void SendRequest<Renderer>(Request& request) { SendRequestToRenderer(request); }

	template<>
	void SendRequest<EntityManager>(Request& request) { SendRequestToEntityManager(request); }

	template <typename Receiver>
	MessageResponse Query(unsigned int message) { return 0; }

	template<>
	MessageResponse Query<Framework>(unsigned int message) { return QueryFramework(message); }
private:
	MessageResponse SendEventToEM(Request nEvent);
	MessageResponse QueryFramework(unsigned int message);

	void SendRequestToRenderer(Request& request);
	void SendRequestToEntityManager(Request& request);

};

