#include <iostream>
#include <windows.h>

#include "field.h"

using namespace std;

int nConsoleWidth, nConsoleHeight;
DWORD prev_mode;

void configureConsole();
void getConsoleWH();


int main()
{
    configureConsole();
    getConsoleWH();

    Field field(nConsoleWidth, nConsoleHeight);
    while (true) {
        field.FindPath();
        if (field.finishProgram) break;
        field.Clean();
    }

    return 0;
}


void configureConsole()
{
    int suitableFontSize = 24;

    // установка размера шрифта в консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    fontInfo.dwFontSize.Y = suitableFontSize;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    // установка размера буфера экрана равным текущему размеру окна
    getConsoleWH();
    COORD newScreenBufferSize;
    newScreenBufferSize.X = ::nConsoleWidth;
    newScreenBufferSize.Y = ::nConsoleHeight;
    if(!SetConsoleScreenBufferSize(hConsole, newScreenBufferSize)) {
        cout << "\nError in " << to_string(__LINE__) << " line: " << GetLastError();
        exit(-1);
    }

    // открытие консоли во весь экран
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    // сделать курсор невидимым
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);

    // чтение текущего режима консоли
    GetConsoleMode(hConsole, &::prev_mode);
}

void getConsoleWH()
{
    HANDLE hWndConsole;
    if(hWndConsole = GetStdHandle(-12))
    {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if(GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
        {
            ::nConsoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            ::nConsoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else exit(-1);
    }
    else exit(-1);
}
