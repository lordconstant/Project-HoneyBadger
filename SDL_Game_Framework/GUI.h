// Corey Bradford - University of Bolton - 1202670

#pragma once

#include "GUIButton.h"
#include "GUIBox.h"
#include "GUIDropDown.h"

class GUI{
private:
	GUI(void);
public:
	~GUI(void);

	static GUIButton* addButton(int x, int y, string file, int col = 1, int row = 1);
	static GUIButton* addButton(int x, int y, string file, string mask, int col = 1, int row = 1);
	static GUIBox* addBox(int x, int y, string file, int col = 1, int row = 1);
	static GUIBox* addBox(int x, int y, string file, string mask, int col = 1, int row = 1);
	static GUIBox* addBox(int x, int y, int w, int h, int r = 0, int g = 0, int b = 0);
	static GUIDropDown* addDropDown(int x, int y, char* file, int col = 1, int row = 1);
};