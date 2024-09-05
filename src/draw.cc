#include "draw.h"

#include <windows.h>

using namespace std;

extern int nConsoleWidth;


void __SetPosition(short x, short y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!SetConsoleCursorPosition(handle, coord)) {
        cout << "\nError: " << GetLastError() << "\n";
        exit(-1);
    }
}

void __SetColor(Color color)
{
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (WORD) color);
}

void draw::PaintPoint(int realX, int realY, PointType pointType)
{
    __SetPosition(realX, realY);
    __SetColor(POINT_COLOR[pointType]);
    cout << string(2, pointType);
}

void draw::RefreshField(std::vector<Point>& field)
{
    __SetPosition(0, 0);
    for (int i = 0; i < field.size() - 1; ++i) {
        if (i == 0 || field[i].type != field[i - 1].type) {
            if (field[i].type == PointType::PASS) __SetColor(POINT_COLOR[PointType::PASS]);
            else if (field[i].type == PointType::WALL) __SetColor(POINT_COLOR[PointType::WALL]);
            else if (field[i].type == PointType::START) __SetColor(POINT_COLOR[PointType::START]);
            else if (field[i].type == PointType::DESTINATION) __SetColor(POINT_COLOR[PointType::DESTINATION]);
        }
        cout << string(2, ' ');
    }
    cout << ' ';
}

void draw::DrawPath(vector<Point>& path, int fieldWidth)
{
    int delayMS;
    size_t threshold1 = static_cast<size_t>(1.5 * fieldWidth);
    size_t threshold2 = static_cast<size_t>(2.5 * fieldWidth);

    if (path.size() < threshold1) delayMS = 30;
    else if (path.size() < threshold2) delayMS = 20;
    else delayMS = 10;

    __SetColor(POINT_COLOR[PointType::PATH]);
    for (int i = 1; i < path.size() - 1; ++i) {
        __SetPosition(path[i].getRealX(), path[i].getRealY());
        cout << string(2, PointType::PATH);
        this_thread::sleep_for(chrono::milliseconds(delayMS));
    }
}

void draw::CleanField(int fieldSize)
{
    __SetPosition(0, 0);
    __SetColor(POINT_COLOR[PointType::PASS]);
    for (int i = 0; i < fieldSize - 1; ++i) {
        cout << string(2, PointType::PASS);
    }
}

void draw::NoPathFound()
{
    const int PHRASE_LENGTH = 47 + 4;  // plus side margin

    __SetColor(Color::PATH_NOT_FOUND);
    if (nConsoleWidth < PHRASE_LENGTH) {
        string message = "Path was not found";
        __SetPosition((nConsoleWidth - message.size()) / 2, 1);
        cout << message;
    }
    else {
        int indentX = (nConsoleWidth - PHRASE_LENGTH) / 2;
        int indentY = 1;
        __SetPosition(indentX, indentY + 0); cout << "     ____       _   _   ";
        __SetPosition(indentX, indentY + 1); cout << "    |  _ \\ __ _| |_| |__   __      ____ _ ___  ";
        __SetPosition(indentX, indentY + 2); cout << "    | |_) / _` | __| '_ \\  \\ \\ /\\ / / _` / __|  ";
        __SetPosition(indentX, indentY + 3); cout << "    |  __/ (_| | |_| | | |  \\ \\V  \\V / (_| \\__ \\  ";
        __SetPosition(indentX, indentY + 4); cout << "    |_|   \\__,_|\\__|_| |_|   \\_/\\_/ \\__,_|___/  ";
        __SetPosition(indentX, indentY + 5); cout << "               _      __                       _  ";
        __SetPosition(indentX, indentY + 6); cout << "   _ __   ___ | |_   / _| ___  _   _ _ __   __| |  ";
        __SetPosition(indentX, indentY + 7); cout << "  | '_ \\ / _ \\| __| | |_ / _ \\| | | | '_ \\ / _` |  ";
        __SetPosition(indentX, indentY + 8); cout << "  | | | | (_) | |_  |  _| (_) | |_| | | | | (_| |  ";
        __SetPosition(indentX, indentY + 9); cout << "  |_| |_|\\___/ \\__| |_|  \\___/ \\__,_|_| |_|\\__,_|  ";
        __SetPosition(indentX, indentY + 10); cout << string(PHRASE_LENGTH, ' ');
    }
}
