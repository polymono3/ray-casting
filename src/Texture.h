#pragma once
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

class Texture
{
public:
	Texture(const std::string& filePath, SDL_Renderer* renderer);
	Texture();
	~Texture();
	bool loadFromFile(const char* filePath, SDL_Renderer* renderer);
	void free();
	void render(SDL_Renderer* renderer, int x, int y);
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

private:
	SDL_Texture* m_texture;
	int m_width;
	int m_height;
};