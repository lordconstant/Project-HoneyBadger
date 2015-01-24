#pragma once

#include "UnitTest++.h"
#include "GUI.h"

TEST(GUITestClass){
	CHECK(GUI::addBox(0,0,0,0,0,0,0));
	CHECK(GUI::addButton(0,0,"images/sword_icon.png"));
	CHECK(GUI::addDropDown(0,0,"images/sword_icon.png"));
}