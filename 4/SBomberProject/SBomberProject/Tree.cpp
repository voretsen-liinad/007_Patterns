
#include <iostream>

#include "Tree.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool TreeA::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

bool TreeB::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void TreeA::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Green);
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 6);
	cout << "   ##   ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 5);
	cout << "  #  #  ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 4);
	cout << " #    # ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "#      #";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 2);
	cout << " ###### ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "   ##   ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
	cout << "   ##   ";
}

void TreeB::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_LightGreen);
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 6);
	cout << "    ###    ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 5);
	cout << "  ##   ##  ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 4);
	cout << " ##     ## ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "  ##   ##  ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 2);
	cout << "    ###    ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "     #     ";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
	cout << "    ###    ";
}