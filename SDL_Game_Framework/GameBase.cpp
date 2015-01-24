#include "GameBase.h"

SDL_Surface* GameBase::screen_surface = NULL;
SDL_Surface* GameBase::background_surface = NULL;

/*
Initialise the SDL.
SDL functions  return 0 on success and <0 for failure so do the same here.
return 0 if successful
*/
int GameBase::initSDL(int width, int height){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0){
		cout << "Unable to initialise SDL\n\nPROGRAM TERMINATED\n\n";
		system("pause");
		return -1;
	}
	// So we have managed to initialise the SDL systems so make sure we
	// uninitialise them when the program terminates
	atexit(SDL_Quit);

	// Now initialise  the screen this will initialise event handling as well
	screen_surface = SDL_SetVideoMode(width, height, 0,
			SDL_HWSURFACE | SDL_DOUBLEBUF);
	// Make sure we have got the screen before moving on
	if(screen_surface == NULL) {
		cout << "Unable to initialise display window\n\nPROGRAM TERMINATED\n\n";
		system("pause");
		return -1;
	}
	// Resize the console window to make it less obvious
	console.setSize(30,10,false);
	// Get default grey background
	background_surface = getSurface(width, height, 0, 0, 0);

	// SDL functions return 0 on success
	return 0;
}

SDL_Surface* GameBase::getSurface(int width, int height, int red, int green, int blue){
	Uint32 rmask, gmask, bmask, amask;
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface *scr = SDL_GetVideoSurface();
	SDL_Surface *temp;
	temp = SDL_CreateRGBSurface(scr->flags, width, height,
								32, rmask, gmask, bmask, amask);
	SDL_Surface* newSurface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	SDL_FillRect(newSurface, NULL, 
		SDL_MapRGB(newSurface->format, red, green, blue));
	return newSurface;
}

GameBase::GameBase(void){
	screen = screen_surface;
	bg = background_surface;
	width = screen->w;
	height = screen->h;
	mouseX = mouseY = 0;
	cout << "Screen size " << width << " x " << height << endl;

	fs_white = new AWFont("vera_white.bmp", "vera.dat");
	fs_green = new AWFont("vera_green.bmp", "vera.dat");
	fs_red = new AWFont("vera_red.bmp", "vera.dat");
}

GameBase::~GameBase(void){
	delete fs_white;
	delete fs_green;
	delete fs_red;
	SDL_FreeSurface(bg);
}

void GameBase::start(){
	gameLoop();
}

int GameBase::getScreenNum(){
	return screenNum;
}

void GameBase::setBackground(int red, int green, int blue){
	bg = getSurface(width, height, red, green, blue);
}

void GameBase::setBackground(char *imageFileName){
	// Get the background image
	SDL_Surface * temp = IMG_Load(imageFileName);
	if(temp != NULL){
		bg = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
	}
	else{
		cout << "Unable to locate image file " << imageFileName << endl;
	}
}

bool GameBase::addSound(char* filename, string name){
	return AudioManager::getInstance()->addSound(filename, name);
}

void GameBase::playSound(string name){
	AudioManager::getInstance()->playSound(name);
}

void GameBase::getUserInput(){
	SDL_Event an_event;
	if(SDL_PollEvent(&an_event)){
		keyDown = keyUp = 0;
		switch(an_event.type)
		{
		case SDL_QUIT:
			gameover = true;
			screenNum = -1;
			break;
		case SDL_KEYDOWN:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyDown = an_event.key.keysym.sym;
			gameover = ((keyDown & SDLK_ESCAPE) == SDLK_ESCAPE);
			onKeyPressed();
			break;
		case SDL_KEYUP:
			ctrlPressed = ((an_event.key.keysym.mod & KMOD_CTRL) == KMOD_CTRL);
			shiftPressed = ((an_event.key.keysym.mod & KMOD_SHIFT) == KMOD_SHIFT);
			altPressed = ((an_event.key.keysym.mod & KMOD_ALT) == KMOD_ALT);
			keyUp = an_event.key.keysym.sym;
			onKeyReleased();
			break;
		case SDL_MOUSEMOTION:
			pmouseX = mouseX;
			pmouseY = mouseY;
			mouseX = an_event.motion.x;
			mouseY = an_event.motion.y;
			onMouseMoved();
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			onMousePressed();
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButton = an_event.button.button; // SDL_BUTTON_LEFT)
			mouseX = an_event.button.x;
			mouseY = an_event.button.y;
			onMouseReleased();
			break;
		default:
			// An event that we do not need to process
			break;
		} // end of poll event switch
	} // end if

}

void GameBase::gameLoop(){
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

int GameBase::enableKeyRepeat(int first, int repeat){
	return SDL_EnableKeyRepeat(first, repeat);

}

int GameBase::print(string value, int x, int y, int color){
	return (getFontToUse(color))->print_string(value.c_str(), x, y);
}

int GameBase::print(const char* value, int x, int y, int color){
	return getFontToUse(color)->print_string(value, x, y);
}

int GameBase::print(int value, int x, int y, int color){
	return getFontToUse(color)->print_integer(value, x, y);
}

int GameBase::print(float value, int x, int y, int color){
	return getFontToUse(color)->print_float(value, x, y);	
}


AWFont* GameBase::getFontToUse(int color){
	switch(color){
	case GREEN:
		return fs_green;
	case WHITE:
		return fs_white;
	case RED:
		return fs_red;
	default:
		return fs_green;
	}
}


