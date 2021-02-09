#include "SimpleGameEngine.h"
#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

SimpleGameEngine::SimpleGameEngine(int windowWidth, int windowHeight, const std::string& name) :
	m_window(nullptr),
	m_renderer(nullptr),
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_running(false)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw std::runtime_error("Failed to initialize SDL. Error: " + std::string(SDL_GetError()) + '\n');
	}

	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (!m_window)
	{
		throw std::runtime_error("Failed to create window. Error: " + std::string(SDL_GetError()) + '\n');
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		throw std::runtime_error("Failed to create renderer. Error: " + std::string(SDL_GetError()) + '\n');
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		throw std::runtime_error("Failed to initialize SDL_image. Error: " + std::string(IMG_GetError()) + '\n');
	}
}

SimpleGameEngine::~SimpleGameEngine()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void SimpleGameEngine::start()
{
	m_running = true;
	Uint32 lastTime = SDL_GetTicks();

	while (m_running)
	{
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		handleEvents();
		logic(deltaTime);
		render();
	}
}

void SimpleGameEngine::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			m_running = false;
	}
	m_keyState = SDL_GetKeyboardState(nullptr);
}

void SimpleGameEngine::logic(float deltaTime)
{
}

void SimpleGameEngine::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderPresent(m_renderer);
}

void SimpleGameEngine::setup()
{
}

