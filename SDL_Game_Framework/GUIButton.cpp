#include "GUIButton.h"

GUIButton::GUIButton(int x, int y, string file, int col, int row){
	m_row = row;
	m_col = col;
	m_sprite = new AWSprite(file, col, row, false);

	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);

	m_font = new AWFont("vera_white.bmp", "vera.dat");

	m_sprite->set_auto_animate(100);

	m_enabled = true;
	m_clicked = false;

	clickTime = 30;

	m_text = "";
}

GUIButton::GUIButton(int x, int y, string file, string mask, int col, int row){
	m_row = row;
	m_col = col;
	m_sprite = new AWSprite(file, col, row, mask, false);

	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);

	m_font = new AWFont("vera_white.bmp", "vera.dat");

	m_sprite->set_auto_animate(100);

	m_enabled = true;
	m_clicked = false;

	clickTime = 30;

	m_text = "";
}

GUIButton::~GUIButton(void){
	delete m_sprite;
	if (m_font != NULL){
		delete m_font;
	}
}

bool GUIButton::update(int SDLButton){
	if (m_enabled){
		animated = false;
		m_clicked = false;
		clickTime++;
		m_mButton = SDL_GetMouseState(&m_mXpos, &m_mYpos);

		if (m_mXpos > m_sprite->get_x() && m_mXpos < m_sprite->get_x() + m_sprite->get_width()){
			if (m_mYpos > m_sprite->get_y() && m_mYpos < m_sprite->get_y() + m_sprite->get_height()){
				m_sprite->set_animation_subset(HOVER * m_col, ((HOVER + 1) * m_col) -1);
				animated = true;
				if (m_mButton == SDL_BUTTON(SDLButton)){
					if (clickTime > 30){
						m_clicked = true;
						clickTime = 0;
					}
				}
			}
		}

		if(!animated){
			m_sprite->set_animation_subset(NORMAL * m_col, ((NORMAL + 1) * m_col) - 1);
		}
		m_sprite->update_everything();

		m_font->print_string(m_text, m_sprite->get_x(), m_sprite->get_y() + m_sprite->get_width() - 10);
		return m_clicked;
	}
	return false;
}

void GUIButton::enabled(bool isEnabled){
	m_enabled = isEnabled;
}

void GUIButton::setText(char* text){
	m_text = text;
}

void GUIButton::setText(std::string text){
	m_text = text;
}

void GUIButton::setPosition(int x, int y){
	m_sprite->set_world_position(x - (m_sprite->get_width() / 2), y - (m_sprite->get_height() / 2));
}
	
int GUIButton::xPos(){
	return m_sprite->get_x() + (m_sprite->get_width() / 2);
}

int GUIButton::yPos(){
	return m_sprite->get_y() + (m_sprite->get_height() / 2);
}