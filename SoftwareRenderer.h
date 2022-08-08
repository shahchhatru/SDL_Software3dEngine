#ifndef SOFTWARERENDERER_H
#define SOFTWARERENDERER_H
#define _USE_MATH_DEFINES
#include"SDL.h"
#include<iostream>
#include"Camera.h"
#include"Projection.h"
#include"Object3d.h"
#include"ObjReader.h"
#include"cmath"
class SoftwareRender {
public:
	int WIDTH = 1200;
	int HEIGHT = 800;
	int FPS = 60;
	SDL_Renderer* renderer;
	SDL_Window* window;
	bool isRunning;
	bool fullscreen;
	int flags;
	Projection* proj;
	Camera* cam;
	Object3d* object3d;
	ObjReader* reader;
	SDL_bool done;
	std::array<float, 3> cam_pos;
	int H_HEIGHT;
	int H_WIDTH;
	int frameDelay;
	int delaytime=0;

	void init() {
		cam_pos = { {-5,6,-55} };
		H_WIDTH = WIDTH / 2;
		H_HEIGHT = HEIGHT / 2;
		fullscreen = false;
		FPS = 60;
		frameDelay = 1 / FPS;
		create_objects();
		initializeSDL();
		
		destroy();
		
		


	}
	void create_objects() {
		
		cam = new Camera(WIDTH, HEIGHT, cam_pos);
		cam->create_all_matrix();
		proj = new Projection(H_WIDTH, H_HEIGHT, cam);
		get_object_from_file((char*)"resources/house.obj");
		object3d->rotate_y(M_PI / 4);
	}

	void get_object_from_file(char* filename) {
		reader = new ObjReader();
		reader->read(filename);
		reader->readfaces(filename);
		
		object3d = new Object3d(reader->vvertices, reader->faces, cam, proj);
		//ObjReader::display_vertices(object3d->vertices);
	}
	void initializeSDL() {
		fullscreen = false;
		flags = 0;
		flags = SDL_WINDOW_RESIZABLE;
		if (fullscreen) {
			flags = flags | SDL_WINDOW_FULLSCREEN;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			std::cout << "Subsystems Initialized!\n";

			window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, flags);
			if (window) {
				std::cout << "Window Created!\n";
				SDL_SetWindowMinimumSize(window, 100, 100);
			}
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				std::cout << "Renderer created!\n";
				//SDL_SetRenderDrawBlendMode(renderer, );
				isRunning = true;

				run();
			}

			
		}




	}

	void run() {
		while (true) {
			int frameStart = SDL_GetTicks();
			update();
			handleEvents();

			
			//SDL_RenderClear(renderer);
			
			int frame_time = SDL_GetTicks() - frameStart;
			if (frameDelay > frame_time) {
				delaytime=frameDelay - frame_time;
			}
		}
	}

	void handleEvents() {
		//the only event we'll check is the  SDL_QUIT event.
		SDL_Event event;
		SDL_PollEvent(&event);
		
		//object3d->draw(renderer);
		//cam->control(&event,isRunning);
		
	}

	void update() {
		//SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
		//SDL_RenderClear(renderer);
		
		
		render();
		//if things could update the code would go in here.
		//SDL_RenderPresent(renderer);
	}

	void render() {
		//

		object3d->draw(renderer,delaytime);
		//SDL_RenderPresent(renderer);
	}

	void destroy() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}


};








#endif

	