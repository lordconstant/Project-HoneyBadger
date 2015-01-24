#include "GUI.h"

GUI::GUI(){

}

GUI::~GUI(){

}

GUIButton* GUI::addButton(int x, int y, string file, int col, int row){
	return new GUIButton(x, y, file, col, row);
}

GUIButton* GUI::addButton(int x, int y, string file, string mask, int col, int row){
	return new GUIButton(x, y, file, mask, col, row);
}

GUIBox* GUI::addBox(int x, int y, string file, int col, int row){
	return new GUIBox(x, y, file, col, row);
}

GUIBox* GUI::addBox(int x, int y, string file, string mask, int col, int row){
	return new GUIBox(x, y, file, mask, col, row);
}

GUIBox* GUI::addBox(int x, int y, int w, int h, int r, int g, int b){
	return new GUIBox(x, y, w, h, r, g, b);
}

GUIDropDown* GUI::addDropDown(int x, int y, char* file, int col, int row){
	return new GUIDropDown(x, y, file, col, row);
}