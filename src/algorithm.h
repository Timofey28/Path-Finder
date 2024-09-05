#pragma once

#include "point.h"
#include "draw.h"


class Algorithm
{
public:
    Algorithm() {}
    void FindShortestPath(std::vector<Point>& field, int fieldWidth, int fieldHeight);

    int shortestPathsAmount;
    std::vector<Point> shortestPath;

private:
    bool __FitType(Point point);
};
