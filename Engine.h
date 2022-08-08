#ifndef ENGINE_H
#define ENGINE_H


class Engine {
private:
	Engine* s_Instance;
	bool isRunning=true;
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	/*
	Engine();
	Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}
	*/

	bool Init() {


		return 0;

	}
	bool Clean() {

	}
	void Quit() {

	}
	void Update() {
		std::cout << "updating" << std::endl; 
	}

	void Render() {
	}

	void Events() {

	}
	inline bool  get_isRunning() {
		return isRunning;
	}
}

#endif











;
