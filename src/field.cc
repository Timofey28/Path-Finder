#include "field.h"

#include "draw.h"

using namespace draw;


Field::Field(int consoleWidth, int consoleHeight)
{
    width_ = consoleWidth / 2;
    height_ = consoleHeight;
    destinationIndex_ = -1;
    finishProgram = false;
}


void Field::init()
{
    field_.resize(width_ * height_);
    for (int i = 0; i < field_.size(); ++i) {
        field_[i] = Point(i, width_);
    }
    startIsChosen_ = false;
    destinationIsChosen_ = false;
}


void Field::FindPath()
{
    init();
    while (true) {
        mouseInput_.GetClickInfo();
        Point clickedPoint(mouseInput_.X, mouseInput_.Y);
        int pointNumber = mouseInput_.Y * width_ + mouseInput_.X / 2;

        if (mouseInput_.buttonPressed == ButtonPressed::LEFT) {
            if (field_[pointNumber].type == PointType::DESTINATION) {
                destinationIsChosen_ = false;
            }
            else if (field_[pointNumber].type == PointType::START) {
                if (destinationIsChosen_) {
                    PaintPoint(field_[destinationIndex_].getRealX(), field_[destinationIndex_].getRealY(), PointType::START);
                    destinationIsChosen_ = false;
                    field_[pointNumber].type = PointType::WALL;
                    field_[destinationIndex_].type = PointType::START;
                }
                else startIsChosen_ = false;
            }
            field_[pointNumber].type = PointType::WALL;
            PaintPoint(clickedPoint.getRealX(), clickedPoint.getRealY(), PointType::WALL);
        }
        else if (mouseInput_.buttonPressed == ButtonPressed::RIGHT) {
            if (field_[pointNumber].type == PointType::DESTINATION) {
                destinationIsChosen_ = false;
            }
            else if (field_[pointNumber].type == PointType::START) {
                if (destinationIsChosen_) {
                    PaintPoint(field_[destinationIndex_].getRealX(), field_[destinationIndex_].getRealY(), PointType::START);
                    destinationIsChosen_ = false;
                    field_[pointNumber].type = PointType::PASS;
                    field_[destinationIndex_].type = PointType::START;
                }
                else startIsChosen_ = false;
            }
            field_[pointNumber].type = PointType::PASS;
            PaintPoint(clickedPoint.getRealX(), clickedPoint.getRealY(), PointType::PASS);
        }

        else if (mouseInput_.buttonPressed == ButtonPressed::CTRL_LEFT) {
            if (startIsChosen_ && field_[pointNumber].type != PointType::START) {
                if (destinationIsChosen_ && field_[pointNumber].type != PointType::DESTINATION) {
                    PaintPoint(field_[destinationIndex_].getRealX(), field_[destinationIndex_].getRealY(), PointType::PASS);
                    field_[destinationIndex_].type = PointType::PASS;
                }
                else destinationIsChosen_ = true;
                destinationIndex_ = pointNumber;
                field_[pointNumber].type = PointType::DESTINATION;
                PaintPoint(clickedPoint.getRealX(), clickedPoint.getRealY(), PointType::DESTINATION);
            }
            else {
                startIsChosen_ = true;
                field_[pointNumber].type = PointType::START;
                PaintPoint(clickedPoint.getRealX(), clickedPoint.getRealY(), PointType::START);
            }
        }

        else if (mouseInput_.buttonPressed == ButtonPressed::WHEEL) {
            if (startIsChosen_ && destinationIsChosen_) break;
            else {
                // todo: добавить вывод сообщения об ошибке
            }
        }
    }

    algorithm_.FindShortestPath(field_, width_, height_);
    this_thread::sleep_for(500ms);
    draw::RefreshField(field_);
    if (algorithm_.shortestPath.size()) DrawPath(algorithm_.shortestPath, width_);
    else draw::NoPathFound();

    mouseInput_.GetMenuOption();
    if (mouseInput_.buttonPressed == ButtonPressed::RIGHT) finishProgram = true;
}

void Field::Clean()
{
    draw::CleanField(field_.size());
}
