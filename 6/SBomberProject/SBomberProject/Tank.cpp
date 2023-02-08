
#include <iostream>
#include <random>

#include "time.h"
#include "Tank.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool Tank::isInside(double x1, double x2) const
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


void Tank::SendAMessage() {
	srand(time(0));
	int x = rand() % 5;
	switch (x) {
	case 0:
		pMediator->NotifyAllRecievers(this, "You can not win!");
		break;
	case 1:
		pMediator->NotifyAllRecievers(this, "We will destroy you!");
		break;
	case 2:
		pMediator->NotifyAllRecievers(this, "You will be defeated!");
		break;
	case 3:
		pMediator->NotifyAllRecievers(this, "We are stronger than you!");
		break;
	case 4:
		pMediator->NotifyAllRecievers(this, "You are just pathetic!");
		break;
	default:
		break;
	}
}


void Tank::Draw() 
{
	MyTools::ScreenSingleton::getInstance().SetColor(CC_Brown);
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 3);
	cout << "    #####";
	MyTools::ScreenSingleton::getInstance().GotoXY(x-2, y - 2);
	cout << "#######   #";
	MyTools::ScreenSingleton::getInstance().GotoXY(x, y - 1);
	cout << "    #####";
	MyTools::ScreenSingleton::getInstance().GotoXY(x,y);
	cout << " ###########";
	SendAMessage();
}

