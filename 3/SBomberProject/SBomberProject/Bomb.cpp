
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}

/*
void BombDecorator::Draw() const {
    bomb.Draw();
    MyTools::ScreenSingleton::getInstance().GotoXY(bomb.GetX(), bomb.GetY() - 1);
    cout << "|";
}
*/

void Bomb::BombIterator::reset() { currentIndex = -1; pBomb = nullptr; }

Bomb::BombIterator& Bomb::BombIterator::operator++ () {
	currentIndex++;
	if (currentIndex == -1) currentIndex = 0;
	for (; currentIndex < vec.size(); currentIndex++) {
		pBomb = dynamic_cast<Bomb*>(vec[currentIndex]);
		if (pBomb != nullptr) break;
	}
	if (currentIndex == vec.size()) {
		currentIndex = -1;
		pBomb = nullptr;
	}
	return *this;
}

Bomb::BombIterator Bomb::BombIterator::operator-- () {
	if (currentIndex == -1) currentIndex = vec.size() - 1;
	for (; currentIndex >= 0; currentIndex--) {
		pBomb = dynamic_cast<Bomb*>(vec[currentIndex]);
		if (pBomb != nullptr) break;
	}
	if (currentIndex == -1) pBomb = nullptr;
	return *this;
}

Bomb* Bomb::BombIterator::operator* () {
	return dynamic_cast<Bomb*>(vec.at(currentIndex));
}

bool Bomb::BombIterator::operator== (BombIterator it) {
	if (currentIndex == it.currentIndex && pBomb == it.pBomb && vec == it.vec) return true; \
	else return false;
}

bool Bomb::BombIterator::operator!= (BombIterator it) {
	return !(*this == it);
}

