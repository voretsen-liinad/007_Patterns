#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};

class BombDecorator : public DynamicObject {
public: 
	BombDecorator(Bomb* _bomb) : bomb(*_bomb) {}
	~BombDecorator() {}
	void Move(uint16_t time) override { bomb.Move(time); };
	
	void Draw() const override;

	inline void SetPos(double nx, double ny) override { bomb.SetPos(nx, ny); };

	inline double GetY() const override { return bomb.GetY(); };
	inline double GetX() const override { return bomb.GetX(); };

	inline void SetWidth(uint16_t widthN) override { bomb.SetWidth(widthN); };
	inline uint16_t GetWidth() const override { return bomb.GetWidth(); };

private:
	Bomb bomb;
};

