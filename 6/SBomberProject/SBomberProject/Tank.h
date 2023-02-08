#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"
#include "Mediator.h"

class Tank : public DestroyableGroundObject
{
public:
	Tank(Mediator* _pMediator) : pMediator(_pMediator) { }

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() override; 

	void SendAMessage(); 

	Mediator* pMediator;

private:

	const uint16_t score = 30;
};

