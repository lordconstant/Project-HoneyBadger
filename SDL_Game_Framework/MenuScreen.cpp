#include "MenuScreen.h"

MenuScreen::MenuScreen(void){
    screenNum = 0;
    setup();
}


MenuScreen::~MenuScreen(void){
	delete box;
	delete button[0];
	delete button[1];
	delete button[2];
}

void MenuScreen::setup(){
    setBackground("images/Menu_bg.png");

	button[0] = GUI::addButton(screen->w / 2, 250, "images/editor_btn_anim.png", 12, 2);
	button[1] = GUI::addButton(screen->w / 2, 325, "images/game_btn_anim.png", 12, 2);
	button[2] = GUI::addButton(screen->w / 2, 400, "images/Quit_btn.png");

	box = GUI::addBox(screen->w / 2, (screen->h / 2) - 35, "images/btn_border.png");

    start();
}

void MenuScreen::start(){
        gameover = false;
        while(!gameover) {
                SDL_Delay(10);
                getUserInput();
                logic();
                SDL_BlitSurface(bg, NULL, screen, NULL);
                draw();
                SDL_Flip(screen);
                post();
        }
}

void MenuScreen::logic(){
}

void MenuScreen::draw(){
	box->update();	
	if (button[0]->update(SDL_BUTTON_LEFT)){
		screenNum = 1;
		gameover = true;
	}
	if (button[1]->update(SDL_BUTTON_LEFT)){
		screenNum = 2;
		gameover = true;
	}
	if (button[2]->update(SDL_BUTTON_LEFT)){
		screenNum = -1;
		gameover = true;
	}
}

int MenuScreen::getScreenNum(){
        return screenNum;
}

void MenuScreen::onMouseReleased(){

}