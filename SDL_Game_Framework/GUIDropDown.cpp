#include "GUIDropDown.h"

GUIDropDown::GUIDropDown(int x, int y, string file, int col, int row){
	m_sprite = new AWSprite(file, col, row, false);
	m_font = new AWFont("vera_white.bmp", "vera.dat");
	m_sprite->set_world_position(x - m_sprite->get_width() / 2, y - m_sprite->get_height() / 2);
	m_sprite->set_auto_animate(100);

	optionsText = new char*[255];

	selOption = 0;
	numOption = 0;

	m_enabled = true;
	m_clicked = false;
}

GUIDropDown::~GUIDropDown(){
	delete m_sprite;
	delete m_font;
	for (int i = 0; i < numOption; i++){
		delete options[i];
	}
	delete optionsText;
}

int GUIDropDown::update(){
	if (m_enabled){
		selOption = -1;
		m_mButton = SDL_GetMouseState(&m_mXpos, &m_mYpos);
		if (m_mButton == SDL_BUTTON_LEFT){
			if (m_mXpos > m_sprite->get_x() && m_mXpos < m_sprite->get_x() + m_sprite->get_width()){
				if (m_mYpos > m_sprite->get_y() && m_mYpos < m_sprite->get_y() + m_sprite->get_height()){
					m_clicked = true;
				}
			}
		}

		if (m_clicked){
			for (int i = 0; i < numOption; i++){
				options[i]->update_everything();
				m_font->print_string(optionsText[i], options[i]->get_x(), options[i]->get_y());

				if (m_mButton == SDL_BUTTON_LEFT){
					if (m_mXpos > options[i]->get_x() && m_mXpos < options[i]->get_x() + options[i]->get_width()){
						if (m_mYpos > options[i]->get_y() && m_mYpos < options[i]->get_y() + options[i]->get_height()){
							selOption = i;
							m_clicked = false;
						}
					}
				}
			}
		}

		m_sprite->update_everything();

		return selOption;
	}
	return -1;
}

bool GUIDropDown::addOption(char* text, int r, int g, int b){
	if (numOption == MAXOPTIONS){
		return false;
	}

	options[numOption] = new AWSprite(m_sprite->get_width(), 20, r, g, b);
	options[numOption]->set_world_position(m_sprite->get_x(), m_sprite->get_y() + m_sprite->get_height() + (20 * numOption));
	optionsText[numOption] = text;
	numOption++;

	return true;
}

void GUIDropDown::enabled(bool isEnabled){
	m_enabled = isEnabled;
}