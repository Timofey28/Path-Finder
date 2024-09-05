#pragma once

#include <map>
#include <vector>

#include "point.h"


enum Color {
    //
    NORMAL = 15,
    PATH_NOT_FOUND = 4,

    // same color background & text
    BLACK = 0,
    BLUE = 17,
    GREEN = 34,
    CYAN = 51,
    RED = 68,
    MAGENTA = 85,
    GOLD = 102,
    ALMOST_WHITE = 119,
    GRAY = 136,
    BRIGHT_BLUE = 153,
    BRIGHT_GREEN = 170,
    SEA_WAVE = 187,
    BRIGHT_RED = 204,
    BRIGHT_MAGENTA = 221,
    BEIGE = 238,
    WHITE = 255,
};


void __SetPosition(short, short);
void __SetColor(Color);


static std::map<PointType, Color> POINT_COLOR {
    {PointType::PASS, Color::BLACK},
    {PointType::WALL, Color::ALMOST_WHITE},
    {PointType::START, Color::GREEN},
    {PointType::DESTINATION, Color::RED},
    {PointType::PATH, Color::BRIGHT_BLUE},
};


namespace draw
{

    static int currentX = -1;
    static int currentY = -1;

    void PaintPoint(int realX, int realY, PointType pointType);
    void RefreshField(std::vector<Point>& field);
    void DrawPath(std::vector<Point>& path, int fieldWidth);
    void CleanField(int fieldSize);
    void NoPathFound();

}  // namespace draw
