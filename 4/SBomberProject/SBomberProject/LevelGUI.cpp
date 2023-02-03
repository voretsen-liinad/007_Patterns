#include <iostream>

#include "LevelGUI.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void LevelGUI::Draw() const
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
    delete [] buf;
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
}

/*
void __fastcall LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
*/

void __fastcall AbstractLevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}

void LevelGUI1::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_Yellow);

    MyTools::ScreenSingleton::getInstance().GotoXY(x, y);
    char* buf = new (nothrow) char[width + 1];
    if (buf == nullptr)
    {
        return;
    }
    memset(buf, '-', width);
    buf[width] = '\0';
    cout << buf;
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y + height);
    cout << buf;
    delete[] buf;
    buf = nullptr;

    for (size_t i = size_t(y + 1); i < height + y; i++)
    {
        MyTools::ScreenSingleton::getInstance().GotoXY(x, (double)i);
        cout << "||";
        MyTools::ScreenSingleton::getInstance().GotoXY(x + width - 1, (double)i);
        cout << "||";
    }

    MyTools::ScreenSingleton::getInstance().GotoXY(18, 1);
    cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    MyTools::ScreenSingleton::getInstance().GotoXY(40, 1);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    MyTools::ScreenSingleton::getInstance().GotoXY(61, 1);
    cout << "BombsNum: " << bombsNumber;
    MyTools::ScreenSingleton::getInstance().GotoXY(77, 1);
    cout << "Score: " << score;
}

void LevelGUI2::Draw() const
{
    MyTools::ScreenSingleton::getInstance().SetColor(CC_Red);

    MyTools::ScreenSingleton::getInstance().GotoXY(x, y + 5);
    char* buf = new (nothrow) char[width + 1];
    if (buf == nullptr)
    {
        return;
    }
    memset(buf, '%', width);
    buf[width] = '\0';
    cout << buf;
    MyTools::ScreenSingleton::getInstance().GotoXY(x, y + height - 1);
    cout << buf;
    delete[] buf;
    buf = nullptr;

    for (size_t i = size_t(y + 5); i < height + y - 1; i++)
    {
        MyTools::ScreenSingleton::getInstance().GotoXY(x, (double)i);
        cout << "%";
        MyTools::ScreenSingleton::getInstance().GotoXY(x + width - 1, (double)i);
        cout << "%";
    }

    MyTools::ScreenSingleton::getInstance().GotoXY(3 + 10, 3);
    cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    MyTools::ScreenSingleton::getInstance().GotoXY(3 + 10, 4);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    MyTools::ScreenSingleton::getInstance().GotoXY(3 + 10, 5);
    cout << "BombsNum: " << bombsNumber;
    MyTools::ScreenSingleton::getInstance().GotoXY(3 + 10, 6);
    cout << "Score: " << score;
}