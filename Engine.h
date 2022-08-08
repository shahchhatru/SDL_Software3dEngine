#ifndef ENGINE_H
#define ENGINE_H

#include"SDL.h"
#include"Camera.h"
#include"Projection.h"
#include"Object3d.h"
#include"ObjReader.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 800
class Engine {
private:
	Engine* s_Instance;
	bool isRunning=true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int pos_x[2] = {100,400};
	int pos_y[2] = {500,900};
	Projection* proj;
	Camera* cam;
	Object3d* object3d;
	ObjReader* reader;
	std::array<float, 3> cam_pos;
	float frameDelay;
	float delaytime = 0;
	int H_WIDTH ;
	int H_HEIGHT;
	
public:

	bool Init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Failed to initialize :%s",SDL_GetError());
			return false;
		}

		isRunning = true;
		window = SDL_CreateWindow("3d engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (window == nullptr) {
			SDL_Log("Failed to intialize window: %s", SDL_GetError());
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) {
			SDL_Log("Failed to intialize render: %s", SDL_GetError());
			return false;
		}

		cam_pos = { {-5,6,-55} };
		H_WIDTH = SCREEN_WIDTH / 2;
		H_HEIGHT = SCREEN_HEIGHT / 2;
		
		create_objects();
		return true;

	}
	bool Clean() {

	}
	void Quit() {

	}
	void Update() {
		SDL_SetRenderDrawColor(renderer, 0,0 , 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		std::cout << "updating" << std::endl;
		//SDL_Delay(3000);
	}

	void Render() {
		//object3d->set_matrix();
		object3d->set_matrix();
		object3d->draw(renderer);


		/*SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawLine(renderer, pos_x[0], pos_y[0], pos_x[1], pos_y[1]);
		SDL_RenderPresent(renderer);*/
	}

	void run() {
		SDL_Event event;
		while (get_isRunning()) {
			
			while (SDL_PollEvent(&event)) {
				int frameStart = SDL_GetTicks();
				Render();

				SDL_Delay(500);
				//object3d->rotate_y(0.1);
				 object3d->rotate_z(0.1);
				 
				int frame_time = SDL_GetTicks() - frameStart;
				if (frameDelay > frame_time) {
					delaytime = frameDelay - frame_time;
				}

				if (event.type == SDL_QUIT) {
					isRunning = false;
					std::cout << "event detected" << std::endl;
				}

				if (event.type == SDL_KEYDOWN) {
					SDL_Keysym keyvalue = event.key.keysym;
					//	cam->control(&keyvalue);
					switch (event.key.keysym.sym) {
						std::cout << "event detected" << event.key.keysym.sym << std::endl;

					case SDLK_a:
						object3d->rotate_x(0.01);
						std::cout << "a" << std::endl;
						break;
					case SDLK_d:
						object3d->rotate_y(0.01);
						std::cout << "event detected d" << std::endl;
						break;
					case SDLK_f:
						object3d->rotate_z(0.01);
						std::cout << "event detected d" << std::endl;
						break;
					}
				}
				Update();

			}
		

		}

	}

	

	void Events() {
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			isRunning = false;
			std::cout << "event detected" << std::endl;
		}

		if (event.type == SDL_KEYDOWN) {
			SDL_Keysym keyvalue = event.key.keysym;
		//	cam->control(&keyvalue);
			switch (event.key.keysym.sym) {
				std::cout << "event detected" << event.key.keysym.sym << std::endl;

			case SDLK_a:
				object3d->rotate_x(0.01);
				std::cout << "a" << std::endl;
				break;
			case SDLK_d:
				object3d->rotate_y(0.01);
				std::cout << "event detected d" << std::endl;
				break;
			case SDLK_f:
				object3d->rotate_z(0.01);
				std::cout << "event detected d" << std::endl;
				break;
			}
		}
	}

	void create_objects() {

		cam = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, cam_pos);
		cam->create_all_matrix();
		proj = new Projection(H_WIDTH, H_HEIGHT, cam);
		get_object_from_file((char*)"resources/house.obj");
		object3d->rotate_y(M_PI / 4);
		object3d->scale(0.85);
	
		
	}

	void get_object_from_file(char* filename) {
		reader = new ObjReader();
		reader->read(filename);
		reader->readfaces(filename);

		object3d = new Object3d(reader->vvertices, reader->faces, cam, proj);
		//ObjReader::display_vertices(object3d->vertices);
		
	}

	inline bool  get_isRunning() {
		return isRunning;
	}

	inline SDL_Renderer* GetRenderer() {
		return renderer;
	}
}

#endif







/*

			switch (keyvalue.sym) {
				std::cout << "event detected" << event.key.keysym.sym << std::endl;

			case SDLK_a:
				pos_x[0]+=10;
				pos_x[1]+=10;
				break;
			case SDLK_d:
				pos_y[0]+10;
				pos_y[1];
				break;
			case SDLK_f:
				pos_x[0]--;
				pos_x[1]--;
				break;
			case SDLK_g:
				pos_y[0]--;
				pos_y[1]--;
				break;
			default:

				break;
*/



;
