#pragma once

#include <vector>
#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

	class BombIterator;
	
	BombIterator begin(std::vector<DynamicObject*>& _vec); 

	BombIterator end(std::vector<DynamicObject*>& _vec); 


private:

};


/*
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
*/


class Bomb::BombIterator {
public:
	BombIterator(const std::vector<DynamicObject*>& _vec) : vec(_vec), currentIndex(-1), pBomb(nullptr) { ++(*this); }

	void reset(); 

	BombIterator& operator++ ();

	BombIterator operator-- ();

	Bomb* operator* ();

	bool operator== (BombIterator it);

	bool operator!= (BombIterator it); 

	BombIterator begin() { BombIterator it(vec);  return it; }

	BombIterator end() { BombIterator it(vec); it.reset(); return it; }

private:
	const std::vector<DynamicObject*>& vec;
	size_t currentIndex;
	Bomb* pBomb;
};



