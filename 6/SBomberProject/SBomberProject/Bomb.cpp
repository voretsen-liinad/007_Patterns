
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() 
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}