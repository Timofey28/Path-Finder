#pragma once

#include <vector>

#include "mouse_input.h"
#include "algorithm.h"
#include "draw.h"
#include "point.h"


class Field
{
public:
    Field(int consoleWidth, int consoleHeight);
    void FindPath();
    void Clean();

    bool finishProgram;

private:
    void init();

    int width_, height_;
    MouseInput mouseInput_;
    Algorithm algorithm_;
    std::vector<Point> field_;
    bool startIsChosen_, destinationIsChosen_;
    int destinationIndex_;
};
