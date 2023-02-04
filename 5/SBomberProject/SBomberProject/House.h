#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public Observer
{
public:

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override; 

	bool HandleInsideCheck(double x1, double x2) const override;

private:

	const uint16_t score = 40;
};

