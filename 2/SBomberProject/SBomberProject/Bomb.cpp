
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

void BombDecorator::Draw() const {
    bomb.Draw();
    MyTools::ScreenSingleton::getInstance().GotoXY(bomb.GetX(), bomb.GetY() - 1);
    cout << "|";
}
