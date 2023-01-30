
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "=========>";
    MyTools::ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    cout << "===";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    cout << "////";
}
