#include "GUIBox.h"

GUIBox::GUIBox(int x, int y, string file, int col, int row){
	m_row = row;
	m_col = col;
	m_text = "";
	m_sprite = new AWSprite(file, col, row, false);

	m_font = new AWFont("vera_white.bmp", "vera.dat");

	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);
	m_sprite->set_auto_animate(100);

	m_enabled = true;
	m_clicked = false;
}

GUIBox::GUIBox(int x, int y, string file, string mask, int col, int row){
	m_row = row;
	m_col = col;
	m_text = "";
	m_sprite = new AWSprite(file, col, row, mask, false);

	m_font = new AWFont("vera_white.bmp", "vera.dat");

	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);
	m_sprite->set_auto_animate(100);

	m_enabled = true;
	m_clicked = false;
}

GUIBox::GUIBox(int x, int y, int w, int h, int r, int g, int b, int a){
	m_row = 1;
	m_col = 1;
	m_text = "";

	m_sprite = new AWSprite(w, h, r, g, b);
	m_sprite->set_surface_alpha(a);

	m_font = new AWFont("vera_white.bmp", "vera.dat");

	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);

	m_enabled = true;
	m_clicked = false;
}

GUIBox::~GUIBox(){
	if (m_sprite){
		delete m_sprite;
	}

	if (m_font){
		delete m_font;
	}
}

bool GUIBox::update(){
	m_mButton = SDL_GetMouseState(&m_mXpos, &m_mYpos);
	m_clicked = false;	
	if (m_enabled){
		m_sprite->update_everything();
			m_font->print_string(m_text, m_sprite->get_x(), m_sprite->get_y());

		if (m_mXpos > m_sprite->get_x() && m_mXpos < m_sprite->get_x() + m_sprite->get_width()){
			if (m_mYpos > m_sprite->get_y() && m_mYpos < m_sprite->get_y() + m_sprite->get_width()){
				m_clicked = true;
			}
		}
	}
	return m_clicked;
}

void GUIBox::setText(char* text){
	m_text = text;
}

void GUIBox::setText(std::string text){
	m_text = text;
}

void GUIBox::setPosition(int x, int y){
	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);
}

void GUIBox::setTranspareny(int r, int g, int b){
	m_sprite->set_transparent_colour(r, g, b);
}

void GUIBox::enabled(bool isEnabled){
	m_enabled = isEnabled;
}

int GUIBox::getX(){
	return m_sprite->get_x();
}

int GUIBox::getY(){
	return m_sprite->get_y();
}