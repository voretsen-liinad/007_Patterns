
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
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
/*
void House::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Yellow);
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
*/

void House::Draw() const
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Yellow);

	for (size_t i = 0; i < 7; i++) {
		MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 6 + i);
		for (size_t j = 0; j < 14; j++) {
			cout << look[i][j]; 
		}
		//cout << endl;
	}
}

void HouseBuilderA::BuildWalls() {
	for (size_t i = 3; i < 6; i++) {
		pHouse->look[i][2] = '#';
		pHouse->look[i][11] = '#';
	}
	for (size_t j = 1; j < 13; j++) {
		pHouse->look[6][j] = '#';
	}
}

void HouseBuilderA::BuildRoof() {
	for (size_t i = 3; i < 11; i++) {
		pHouse->look[0][i] = '#';
	}
	pHouse->look[1][2] = '#'; pHouse->look[1][3] = '#'; pHouse->look[1][10] = '#'; pHouse->look[1][11] = '#';
	for (size_t j = 1; j < 13; j++) {
		pHouse->look[2][j] = '#';
	}
}

void HouseBuilderA::BuildWindows() {
	for (size_t i = 6; i < 9; i++) {
		pHouse->look[3][i] = '_';
		pHouse->look[4][i] = '_';
	}
	pHouse->look[4][5] = '|'; pHouse->look[4][9] = '|';
}

void HouseBuilderB::BuildWalls() {
	for (size_t i = 4; i < 6; i++) {
		pHouse->look[i][3] = '#';
		pHouse->look[i][10] = '#';
	}
	for (size_t j = 2; j < 12; j++) {
		pHouse->look[6][j] = '#';
	}
}

void HouseBuilderB::BuildRoof() {
	for (size_t i = 3; i < 11; i++) {
		pHouse->look[1][i] = '#';
	}
	pHouse->look[2][2] = '#'; pHouse->look[2][11] = '#';
	for (size_t j = 1; j < 13; j++) {
		pHouse->look[3][j] = '#';
	}
}

void HouseBuilderB::BuildChimney() {
	pHouse->look[0][8] = '#';
}

House* HouseDirector::Construct(HouseBuilder& builder) {
	builder.CreateHouse();
	builder.BuildWalls();
	builder.BuildRoof();
	builder.BuildWindows();
	builder.BuildChimney();
	return builder.GetHouse();
}