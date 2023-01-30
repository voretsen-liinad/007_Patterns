#include <iostream>

#include "WinterTank.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void WinterTank::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Blue);
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "    #####";
	MyTools::ScreenSingleton::getInstance().GotoXY(x - 2, y - 2);
	cout << "#######   #";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "    #####";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
	cout << " ###########";
}