#pragma once

#include "UnitTest++.h"
#include "GUI.h"

TEST(GUIDropDownTestClass){
	GUIDropDown* dropDown = GUI::addDropDown(0, 0, "images/sword_icon.png");

	CHECK_EQUAL(true, dropDown->addOption("new option"));
	CHECK_EQUAL(-1, dropDown->update());

	delete dropDown;
}