#pragma once


enum PointType
{
    UNKNOWN,
    PASS = ' ',
    WALL = '#',
    START = 's',
    DESTINATION = 'd',
    PATH = 'p',
};

struct Point
{
    Point(PointType pointType = PointType::PASS) :
        x(-1),
        y(-1),
        type(pointType) {}
    Point(int number, int fieldWidth, PointType pointType = PointType::PASS) :
        x(number % fieldWidth),
        y(number / fieldWidth),
        type(pointType) {}
    Point(short consoleX, short consoleY) :
        x(consoleX / 2),
        y(consoleY),
        type(PointType::UNKNOWN) {}

    short x, y;
    PointType type;
    short getRealX() { return x * 2; }
    short getRealY() { return y; }
};
