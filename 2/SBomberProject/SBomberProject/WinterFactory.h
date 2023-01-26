#pragma once

#include <vector>

#include "GameObject.h"
#include "Ground.h"
#include "House.h"
#include "Tank.h"

class AbstractFactory
{
public:
	virtual Ground* CreateGround() = 0;
	virtual House* CreateHouse() = 0;
	virtual Tank* CreateTank() = 0;
	virtual void CreateLevel1(std::vector<GameObject*>& refStaticObjVec) = 0;
};

class WinterFactory : public AbstractFactory
{
public:
	Ground* CreateGround() override;
	House* CreateHouse() override;
	Tank* CreateTank() override;
	void CreateLevel1(std::vector<GameObject*>& refStaticObjVec) override;
};
