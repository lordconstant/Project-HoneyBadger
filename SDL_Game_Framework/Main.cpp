#include "ScreenManager.h"
#include "TestAll.h"

//uncomment line below to run unitTest
//#define RUNTESTS = true;

int main(int argc, char* argv[]){


        GameBase::initSDL(1280, 720);
#ifndef RUNTESTS
        ScreenManager* myManager = new ScreenManager();

        delete myManager;

#else
	TestAll ta;
	ta.runAllTests();
#endif
	_CrtDumpMemoryLeaks();
        return 0;
}
