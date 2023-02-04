
#include <iostream>

#include "DynamicObject.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}

DestroyableGroundObject* Bomb::CheckDestroyableObjects() {
    DestroyableGroundObject* result = nullptr;
    const double size = this->GetWidth();
    const double size_2 = size / 2;
    //for (size_t i = 0; i < Observers.size(); i++)
    for (std::vector<Observer*>::iterator it = Observers.begin(); it != Observers.end();)
    {
        const double x1 = this->GetX() - size_2;
        const double x2 = x1 + size;
        if ((*it)->HandleInsideCheck(x1, x2))
        {
            result = *it;
            Observers.erase(it);
        }
        else it++;
        return result;
    }
}
