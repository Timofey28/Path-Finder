#pragma once

#include <windows.h>

extern DWORD prev_mode;


enum ButtonPressed
{
    RIGHT,
    WHEEL,
    LEFT,
    CTRL_LEFT,
};


class MouseInput
{
public:
    MouseInput() :
        handle_(GetStdHandle(STD_INPUT_HANDLE)) {}

    void GetClickInfo();
    void GetMenuOption();

    short X, Y;
    ButtonPressed buttonPressed;

private:
    void __EnableMouseInput();

    HANDLE handle_;
    INPUT_RECORD inputRecord_;
    DWORD events_;
};
