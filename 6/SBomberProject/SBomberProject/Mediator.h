#pragma once

#include <vector>

#include "GameObject.h"

class Mediator {
public:
	void AddSender(GameObject* pSender);
	void AddReciever(GameObject* pReciever); 
	void NotifyAllRecievers(GameObject* pSender, const std::string& message); 
private:
	std::vector<GameObject*> Senders;
	std::vector<GameObject*> Recievers;
};