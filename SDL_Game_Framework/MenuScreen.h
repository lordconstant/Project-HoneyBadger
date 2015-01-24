// Christopher Gough - University of Bolton

/*
	Edited by Corey Bradford
	- added chunk loading
	- added collision with solid tiles

*/

#pragma once
#include "gamebase.h"
#include "Editor.h"
#include "GUI.h"

class MenuScreen :public GameBase{
private:
		GUIButton* button[3];
		GUIBox* box;
public:
        void setup();
        void start();
        void logic();
        void draw();
        void onMouseReleased();
        int getScreenNum();

        MenuScreen(void);
        ~MenuScreen(void);
};
