// Corey Bradford - University of Bolton - 1202670

/*
	Edited by Corey Bradford
	- added setText string function
	- added alpha support to colour box constructor
	- changed char* text to string text

	Edited by Christopher Gough
	- added set Transpareny
	- added mask support
*/

#pragma once

#include <string>

#include "GUIElement.h"
class GUIBox : public GUIElement{
private:
	std::string m_text;
	GUIBox(int x, int y, string file, int col = 1, int row = 1);
	GUIBox(int x, int y, string file, string mask, int col = 1, int row = 1);
	GUIBox(int x, int y, int w, int h, int r, int g, int b, int a = 255);
public:
	~GUIBox();

	void enabled(bool isEnabled);

	bool update();
	void setText(char* text);
	void setText(std::string text);
	void setPosition(int x, int y);
	void setTranspareny(int r, int g, int b);
	int getX();
	int getY();

	friend class GUI;
};