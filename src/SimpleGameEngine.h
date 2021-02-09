#pragma once
#include <string>
#include <stdint.h>

struct SDL_Window;
struct SDL_Renderer;

class SimpleGameEngine
{
public:
	SimpleGameEngine(int windowWidth, int windowHeight, const std::string& name = "Game");
	~SimpleGameEngine();

	void start();

protected:
	virtual void handleEvents();
	virtual void logic(float deltaTime);
	virtual void render();
	virtual void setup();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_windowWidth;
	int m_windowHeight;
	bool m_running;
	const uint8_t* m_keyState;

};