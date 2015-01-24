#pragma once

#include "UnitTest++.h"
#include "GUI.h"

TEST(GUIBoxTestClass){
	GUIBox* tempBox = GUI::addBox(0, 0, 0, 0);

	CHECK_EQUAL(0, tempBox->getX());
	CHECK_EQUAL(0, tempBox->getY());
	tempBox->setPosition(10, 10);
	CHECK_EQUAL(10, tempBox->getX());
	CHECK_EQUAL(10, tempBox->getY());
	CHECK_EQUAL(false, tempBox->update());

	delete tempBox;
}