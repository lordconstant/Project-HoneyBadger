// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "GUIElement.h"

const int MAXOPTIONS = 40;

class GUIDropDown :public GUIElement{
	GUIDropDown(int x, int y, string file, int col, int row);
	int selOption;
	int numOption;
	AWSprite* options[MAXOPTIONS];
	char** optionsText;
public:
	~GUIDropDown();

	int update();
	void enabled(bool isEnabled);
	bool addOption(char* text, int r = 0, int g = 0, int b = 0);

	friend class GUI;
};

