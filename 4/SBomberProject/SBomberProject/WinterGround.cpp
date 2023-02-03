#include <iostream>

#include "MyTools.h"
#include "WinterGround.h"

using namespace std;
using namespace MyTools;

void WinterGround::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_LightBlue);

    const size_t bufSize = width + 1;
    char* buf = new (nothrow) char[bufSize];
    if (buf == nullptr)
    {
        return;
    }

    if (vecCrates.size() == 0)
    {
        MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
        memset(buf, '=', bufSize);
        buf[bufSize - 1] = '\0';
        cout << buf;
    }
    else
    {
        const size_t X = size_t(x);
        char c;
        for (size_t i = X; i < width + X; i++)
        {
            c = (isInsideAnyCrater((double)i)) ? ' ' : '=';
            buf[i - X] = c;
        }

        MyTools::ScreenSingleton::getInstance().GotoXY((double)X, y);
        buf[bufSize - 1] = '\0';
        cout << buf;

        for (size_t i = 0; i < vecCrates.size(); i++)
        {
            vecCrates[i].Draw();
        }
    }

    delete[] buf;
}
