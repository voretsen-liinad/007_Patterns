#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

	friend class HouseBuilderA;
	friend class HouseBuilderB;

private:
//protected:

	const uint16_t score = 40;

	char look[7][14] = { ' ' };
};


class HouseBuilder {
public:
	HouseBuilder() : pHouse(nullptr) {};
	virtual ~HouseBuilder() {};
	virtual void CreateHouse() { pHouse = new House; };
	virtual void BuildWalls() {};
	virtual void BuildRoof() {};
	virtual void BuildWindows() {};
	virtual void BuildChimney() {};
	virtual House* GetHouse() { return pHouse; }
protected:
	House* pHouse;
};

class HouseBuilderA : public HouseBuilder {
public:
	void BuildWalls();
	void BuildRoof();
	void BuildWindows();
};

class HouseBuilderB : public HouseBuilder {
public:
	void BuildWalls();
	void BuildRoof();
	void BuildChimney();
};

class HouseDirector {
public:
	House* Construct(HouseBuilder& builder);
};
