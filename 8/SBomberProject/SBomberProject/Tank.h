#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class Tank : public DestroyableGroundObject
{
public:

	Tank() = default;

	Tank(const Tank* _tank) : score(_tank->score) {};

	Tank(const uint16_t& _score) : score(_score) {};

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

	virtual DestroyableGroundObject* Clone() const { return new Tank(this); };

private:

	const uint16_t score = 30;
};

