#include "Mediator.h"

void Mediator::AddSender(GameObject* pSender) {
	for (auto sender : Senders) {
		if (pSender == sender) return;
	}
	Senders.push_back(pSender);
}


void Mediator::AddReciever(GameObject* pReciever) {
	for (auto reciever : Recievers) {
		if (pReciever == reciever) return;
	}
	Recievers.push_back(pReciever);
}


void Mediator::NotifyAllRecievers(GameObject* pSender, const std::string& message) {
	for (auto reciever : Recievers) {
		if (pSender != reciever) reciever->BeNotified(message);
	}
}
