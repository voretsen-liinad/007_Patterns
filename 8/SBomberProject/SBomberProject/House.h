#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	House() = default;

	House(const House* _house) : score(_house->score) {};

	House(const uint16_t& _score) : score(_score) {};

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

	virtual DestroyableGroundObject* Clone() const { return new House(this); };

private:

	const uint16_t score = 40;
};

