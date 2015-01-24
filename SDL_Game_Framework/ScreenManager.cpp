#include "ScreenManager.h"


ScreenManager::ScreenManager(void){
        curScreen = new MenuScreen();
        start();
}


ScreenManager::~ScreenManager(void){
}

void ScreenManager::start(){
        while(curScreen != NULL){
				screenNum = curScreen->getScreenNum();
                changeScreen();
        }
}

void ScreenManager::changeScreen(){
        if(curScreen != NULL){
                delete curScreen;
                curScreen = NULL;
        }

        switch(screenNum){
        case MENU:
                        curScreen = new MenuScreen();
                        break;
        case EDITOR:
                        curScreen = new Editor();
                        break;
        case GAME:
						curScreen = new Game();
                        break;
        default:
                        break;
        }
}