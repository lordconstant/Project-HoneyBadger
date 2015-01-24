// Corey Bradford - University of Bolton - 1202670

/*
	Edited by Corey Bradford
	- Added setText string function
	- changed char* text to string text
*/

#pragma once

#include <string>

#include "GUIElement.h"
class GUIButton : public GUIElement{
private:
	enum STATE{NORMAL, HOVER, CLICKED};
	bool animated;
	GUIButton(int x, int y, string file, int col, int row);
	GUIButton(int x, int y, string file, string mask, int col, int row);
	std::string m_text;

	int clickTime;
public:	
	~GUIButton(void);

	bool update(int SDLButton);
	void enabled(bool isEnabled);
	void setText(char* text);
	void setText(std::string text);

	void setPosition(int x, int y);
	
	int xPos();
	int yPos();

	friend class GUI;
};

