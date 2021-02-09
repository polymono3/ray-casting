#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Vec2f.h"

const int MINIMAP_SIZE = 96;

Map::Map() :
	m_width(0),
	m_height(0)
{
}

bool Map::loadFromFile(const std::string& file)
{
	m_contents.clear();

	std::ifstream mapFile(file);
	if (!mapFile.is_open())
	{
		std::cout << "Failed to load map file: " << file << std::endl;
		return false;
	}

	for (std::string line; std::getline(mapFile, line);)
	{
		std::vector<int> temp;
		std::istringstream ss(line);

		for (int i; ss >> i; )
		{
			temp.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		m_contents.push_back(temp);
	}

	m_width = m_contents[0].size();
	m_height = m_contents.size();

	return true;
}

void Map::drawMinimap(SDL_Renderer* renderer, const Vec2f& playerPos)
{
	int cellSize = MINIMAP_SIZE / m_width;
	SDL_SetRenderDrawColor(renderer, 156, 156, 156, 255);
	SDL_Rect r{ 0,0,MINIMAP_SIZE,MINIMAP_SIZE };
	SDL_RenderFillRect(renderer, &r);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			if (m_contents[i][j] != 0)
			{
				SDL_Rect r{ j*cellSize, i*cellSize, cellSize, cellSize };
				SDL_RenderFillRect(renderer, &r);
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect playerMinimapRect{ (int)playerPos.x * cellSize, (int)playerPos.y * cellSize, cellSize, cellSize };
	SDL_RenderFillRect(renderer, &playerMinimapRect);
}
