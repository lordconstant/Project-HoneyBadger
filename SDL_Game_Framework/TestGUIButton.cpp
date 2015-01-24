#pragma once

#include "UnitTest++.h"
#include "GUI.h"

TEST(GUIButtonTestClass){
	GUIButton* tempButton = GUI::addButton(0, 0, "images/sword_icon.png");

	CHECK_EQUAL(0, tempButton->xPos());
	CHECK_EQUAL(0, tempButton->yPos());
	tempButton->setPosition(10, 10);
	CHECK_EQUAL(10, tempButton->xPos());
	CHECK_EQUAL(10, tempButton->yPos());
	CHECK_EQUAL(false, tempButton->update(1));

	delete tempButton;
}