// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "AWSprite.h"
#include "AWFont.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

class GUIElement{
protected:
	AWFont* m_font;
	AWSprite* m_sprite;

	int m_mXpos, m_mYpos, m_mButton;
	int m_row, m_col;

	bool m_enabled, m_clicked;

public:
	virtual void enabled(bool isEnabled) = 0;
};