#include "Texture.h"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <stdexcept>

Texture::Texture(const std::string& filePath, SDL_Renderer* renderer) :
	m_texture(nullptr),
	m_width(0),
	m_height(0)
{
	SDL_Texture* tex = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface)
	{
		throw std::runtime_error("Failed to load image at " + filePath + "Error: " + std::string(IMG_GetError()) + '\n');
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (!tex)
	{
		throw std::runtime_error("Failed to create texture. Error: " + std::string(IMG_GetError()) + '\n');
	}
	m_width = surface->w;
	m_height = surface->h;

	SDL_FreeSurface(surface);

	m_texture = tex;
}

Texture::Texture() :
	m_texture(nullptr),
	m_width(0),
	m_height(0)
{
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(const char* filePath, SDL_Renderer* renderer)
{
	free();
	SDL_Texture* tex = nullptr;
	SDL_Surface* surface = IMG_Load(filePath);
	if (!surface)
	{
		std::cout << "Failed to load image at " << filePath << ". Error: " << IMG_GetError() << std::endl;
		return false;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (!tex)
	{
		std::cout << "Failed to create texture from surface. Error: " << IMG_GetError() << std::endl;
		return false;
	}
	m_width = surface->w;
	m_height = surface->h;

	SDL_FreeSurface(surface);

	m_texture = tex;
	return true;
}

void Texture::free()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect r{ x - m_width / 2, y - m_height / 2, m_width,m_height };
	SDL_RenderCopy(renderer, m_texture, nullptr, &r);
}
