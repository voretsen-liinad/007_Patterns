#include <iostream>

#include "WinterHouse.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void WinterHouse::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Blue);
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 5);
	cout << "  ########  ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 4);
	cout << "##        ##";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "############";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 2);
	cout << "#          #";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "#          #";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
	cout << "############";
}