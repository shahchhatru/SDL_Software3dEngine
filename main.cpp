#include<iostream>
#include"SDL.h"
#undef main

#include"Engine.h"

int main() {
	
	Engine* eng = new Engine();
	eng->Init();
	float delaytime=0.0f;
	int delay;
	float  frameDelay = 1 / 60;
	eng->run();
	

}

/*
SoftwareRender* soft = new SoftwareRender();
	soft->init();
	int frame_time = SDL_GetTicks() - frameStart;
			if (frameDelay > frame_time) {
				delaytime=frameDelay - frame_time;
			}
*/