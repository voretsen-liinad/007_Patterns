
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    ofstream logOut;

    //=============================================================================================

    void ScreenSingleton::ClrScr()
    {
        system("cls");
    }

    void __fastcall ScreenSingleton::GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t ScreenSingleton::GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t ScreenSingleton::GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void ScreenSingleton::SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    //=============================================================================================

    void __fastcall FileLoggerSingleton::OpenLogFile(const string& FN)
    {
        logOut.open(FN, ios_base::out);
    }

    void FileLoggerSingleton::CloseLogFile()
    {
        if (logOut.is_open())
        {
            logOut.close();
        }
    }

    string GetCurDateTime()
    {
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    }

    void __fastcall FileLoggerSingleton::WriteToLog(const string& str)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << endl;
        }
    }

    void __fastcall FileLoggerSingleton::WriteToLog(const string& str, int n)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << n << endl;
        }
    }

    void __fastcall FileLoggerSingleton::WriteToLog(const string& str, double d)
    {
        if (logOut.is_open())
        {
            logOut << GetCurDateTime() << " - " << str << d << endl;
        }
    }

    //=============================================================================================
   
    void __fastcall LoggerSingleton::OpenLogFile(const string& FN)
    {
        RealSubject.OpenLogFile(FN);
    }

    void LoggerSingleton::CloseLogFile()
    {
        RealSubject.CloseLogFile();
    }

    void __fastcall LoggerSingleton::WriteToLog(const string& str)
    {
        if (logOut.is_open())
        {
            logOut << Counter << " - ";
            Counter++;
        }
        RealSubject.WriteToLog(str);
    }

    void __fastcall LoggerSingleton::WriteToLog(const string& str, int n)
    {
        if (logOut.is_open())
        {
            logOut << Counter << " - ";
            Counter++;
        }
        RealSubject.WriteToLog(str, n);
    }

    void __fastcall LoggerSingleton::WriteToLog(const string& str, double d)
    {
        if (logOut.is_open())
        {
            logOut << Counter << " - ";
            Counter++;
        }
        RealSubject.WriteToLog(str, d);
    }

} // namespace MyTools