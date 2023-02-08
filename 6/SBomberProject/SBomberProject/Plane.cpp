
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

/*
void Plane::Draw() 
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
*/

void Plane::Draw()
{
    DrawBody();
    DrawWings();
    DrawTail();
}


void ColorPlane::DrawBody() {
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "=========>";
}


void ColorPlane::DrawWings() {
    MyTools::ScreenSingleton::getInstance().SetColor(CC_White);
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 3, y + 1);
    cout << "////";
}


void ColorPlane::DrawTail() {
    MyTools::ScreenSingleton::getInstance().SetColor(CC_Red);
    MyTools::ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    cout << "===";
}


void BigPlane::DrawBody() {
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightBlue);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "=============-_";
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y + 1);
    cout << "=============-";
}


void BigPlane::DrawWings() {
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 4, y - 2);
    cout << "\\\\\\";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 4, y - 1);
    cout << "\\\\\\\\";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 4, y + 2);
    cout << "////";
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 4, y + 3);
    cout << "///";
}


void BigPlane::DrawTail() {
    MyTools::ScreenSingleton::getInstance().GotoXY(x - 3, y - 2);
    cout << "===";
    MyTools::ScreenSingleton::getInstance().GotoXY(x - 2, y - 1);
    cout << "===";
}