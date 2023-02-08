#include <iostream>
#include <windows.h>

#include "LevelGUI.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;


void LevelGUI::Draw() 
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_White);

    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    char* buf = new (nothrow) char[width + 1];
    if (buf == nullptr)
    {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    cout << buf;
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y + height);
    cout << buf;
    delete[] buf;
    buf = nullptr;

    for (size_t i = size_t(y); i < height + y; i++)
    {
        MyTools::ScreenSingleton::getInstance().GotoXY(x, (double)i);
        cout << "+";
        MyTools::ScreenSingleton::getInstance().GotoXY(x + width - 1, (double)i);
        cout << "+";
    }

    MyTools::ScreenSingleton::getInstance().GotoXY(3, 1);
    cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    MyTools::ScreenSingleton::getInstance().GotoXY(25, 1);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    MyTools::ScreenSingleton::getInstance().GotoXY(46, 1);
    cout << "BombsNum: " << bombsNumber;
    MyTools::ScreenSingleton::getInstance().GotoXY(62, 1);
    cout << "Score: " << score;


    MyTools::ScreenSingleton::getInstance().SetColor(CC_Red);
    MyTools::ScreenSingleton::getInstance().GotoXY(x + 3, y + height - 1);
    if (Messages.size() != 0) cout << Messages.front();

    ChangeTime(GetTickCount64());
    if ((GetTime() % 3 == 0) && Messages.size() > 1) Messages.pop_front();
}


void __fastcall LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
