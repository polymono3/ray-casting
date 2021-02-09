#pragma once
#include <string>
#include <vector>
#include <SDL.h>

class Vec2f;

class Map
{
public:
	Map();
	bool loadFromFile(const std::string& file);
	int getCell(int row, int col) const { return m_contents[row][col]; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	void drawMinimap(SDL_Renderer* renderer, const Vec2f& playerPos);

private:
	std::vector<std::vector<int>> m_contents;
	int m_width;
	int m_height;
};