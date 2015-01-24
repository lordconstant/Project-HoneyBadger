// Christopher Gough - University of Bolton

#pragma once
#include "MenuScreen.h"
#include "Editor.h"
#include "Game.h"

enum Screens{MENU, EDITOR, GAME};

class ScreenManager{
        GameBase* curScreen;
        int screenNum;
public:
        ScreenManager(void);
        ~ScreenManager(void);

        void start();
        void changeScreen();
};
