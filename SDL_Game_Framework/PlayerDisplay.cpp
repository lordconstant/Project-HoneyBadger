#include "PlayerDisplay.h"

PlayerDisplay::PlayerDisplay(int size, string file){
	bgBox = GUI::addBox(1000, 300, file, 1, 1);
	bgBox->setTranspareny(0, 0, 0);

	expBar = GUI::addBox(66, 330, "images/exp_bar.png", "images/exp_bar_mask.png");
	playerImg = NULL;

	invIcon = new GUIButton* [size];
	eqpIcon = new GUIButton* [EQPINT];

	for(int i = 0; i < size; i++){
		invIcon[i] = NULL;
	}

	for (int i = 0; i < EQPINT; i++){
		eqpIcon[i] = NULL;
	}

	m_size = size;
}

void PlayerDisplay::setIcon(int num, string file, int stackNum){
	int x, y, col;
	char* s = new char[255];
	x = (bgBox->getX()+64)+(64*num);
	col = 0;

	if(num > 9){
		col = 2;
		x-= 64*10;
	}else if(num > 4){
		col = 1;
		x -= 64*5;
	}

	y = (bgBox->getY()+328)+(64*col);

	sprintf(s, "%i", stackNum);

	if(invIcon[num] != NULL){
		clearIcon(num);
	}

	invIcon[num] = GUI::addButton(x, y, file, "images/Icon_Rare_Mask.png", 1, 1);
	invIcon[num]->setText(s);

	s = NULL;
}

void PlayerDisplay::setEquipIcon(int num, string file){
	int x, y, row;
	x = (bgBox->getX() + 248) + (64 * num);
	row = 0;

	if (num > 3){
		row = 2;
		x -= 64 * 4;
	}else if (num > 1){
		row = 1;
		x -= 64 * 2;
	}

	y = (bgBox->getY() + 64) + (64 * row);

	eqpIcon[num] = GUI::addButton(x, y, file, 1, 1);
}

void PlayerDisplay::setPlayerImage(string file){
	if (playerImg != NULL){
		delete playerImg;
		playerImg = NULL;
	}

	playerImg = GUI::addBox(bgBox->getX()+112, bgBox->getY()+128, file, 1, 1);
	playerImg->setTranspareny(1, 1, 1);
}

void PlayerDisplay::clearIcon(int num){
	if (num < 0 || invIcon[num] == NULL){
		return;
	}

	delete invIcon[num];
	invIcon[num] = NULL;
}

void PlayerDisplay::update(Inventory<Item>* playerInv){
	bgBox->update();

	if (playerImg != NULL){
		playerImg->update();
	}

	for (int i = 0; i < m_size; i++){
		if (invIcon[i] != NULL){
			if (invIcon[i]->update(SDL_BUTTON_LEFT)){
				cout << "clicked" << endl;

				if (playerInv->getElement(i)){
					if (!playerInv->getElement(i)->getData()->isDisplayingToolTip()){
						playerInv->getElement(i)->getData()->itemDisplay(invIcon[i]->xPos(), invIcon[i]->yPos() + 24);
					}
					else{
						playerInv->getElement(i)->getData()->stopDisplay();
					}
				}
			}
		}
	}

	for (int i = 0; i < EQPINT; i++){
		if (eqpIcon[i] != NULL){
			if (eqpIcon[i]->update(SDL_BUTTON_LEFT)){
				cout << "clicked" << endl;
			}
		}
	}

	for (int i = 0; i < m_size; i++){
		if (invIcon[i] != NULL){
			if (playerInv->getElement(i)){
				playerInv->getElement(i)->getData()->renderDisplay();
			}
		}
	}
}

void PlayerDisplay::permUpdate(int maxExp, int exp){
	SDL_Rect temp;
	float tempNum;
	tempNum = (400.f/maxExp) * exp;
	temp.x = 35;
	temp.y = 530-tempNum;
	temp.h = tempNum;
	temp.w = 60;

	SDL_FillRect(SDL_GetVideoSurface(), &temp, 6553760);

	expBar->update();
}

PlayerDisplay::~PlayerDisplay(void){
	delete bgBox;
	bgBox = NULL;
	
	for(int i = 0; i < m_size; i++){
		delete invIcon[i];
		invIcon[i] = NULL;
	}

	delete invIcon;
	invIcon = NULL;
}
