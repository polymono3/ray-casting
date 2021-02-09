#include "RayCastDemo.h"
#include <SDL.h>
#include <algorithm>
#include <iostream>
#include "Texture.h"

const float FOV = 3.14159f / 4.0f;
const float LOOK_SENSITIVITY = 2.0f;
const float MAX_RAY_DEPTH = 16.0f;

RayCastDemo::RayCastDemo(int windowWidth, int windowHeight, int rows, int columns) :
	SimpleGameEngine(windowWidth, windowHeight, "Ray Casting"),
	m_numRows(rows),
	m_numCols(columns),
	m_rowHeight(m_windowHeight / rows),
	m_colWidth(m_windowWidth / columns),
	m_showBoundaries(true),
	m_fov(FOV),
	m_lookSensitivity(LOOK_SENSITIVITY),
	m_maxRayDepth(MAX_RAY_DEPTH),
	m_rayInterval(0.1f),
	m_player(16.0f, 16.0f)
{
	setup();
}

void RayCastDemo::handleEvents()
{
	SimpleGameEngine::handleEvents();
	m_player.processKeyboard(m_keyState);
}

void RayCastDemo::logic(float deltaTime)
{
	m_player.update(deltaTime, m_map);
}

void RayCastDemo::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Draw floor
	for (int y = m_numRows / 2; y < m_numRows; ++y)
	{
		Uint8 floorShade = (Uint8)(125.0f * (float)(y - m_numRows / 2.0f) / (m_numRows / 2.0f));
		SDL_SetRenderDrawColor(m_renderer, floorShade, floorShade, floorShade, 255);
		SDL_Rect r{ 0, y * m_rowHeight, m_windowWidth, m_rowHeight };
		SDL_RenderFillRect(m_renderer, &r);
	}
	for (int x = 0; x < m_numCols; ++x)
	{
		float rayAngle = m_player.getViewAngle() - m_fov / 2 + ((float)x / m_numCols) * m_fov;

		float distanceToWall = 0.0f;
		bool hitWall = false;
		bool boundary = false;
		while (!hitWall && distanceToWall < m_maxRayDepth)
		{
			distanceToWall += m_rayInterval;

			Vec2f eye(sinf(rayAngle), cosf(rayAngle));

			int testX = (int)(m_player.getPosition().x + eye.x * distanceToWall);
			int testY = (int)(m_player.getPosition().y + eye.y * distanceToWall);

			// check if the ray goes out of bounds
			if (testX < 0 || testX >= m_map.getWidth() || testY < 0 || testY > m_map.getHeight())
			{
				hitWall = true;
				distanceToWall = m_maxRayDepth;
			}
			else
			{
				if (m_map.getCell(testX, testY) == 1)
				{
					hitWall = true;

					if (m_showBoundaries)
					{
						std::vector<std::pair<float, float>> p;
						for (int i = 0; i < 2; ++i)
						{
							for (int j = 0; j < 2; ++j)
							{
								Vec2f playerToBoundary;
								playerToBoundary.x = (float)testX + i - m_player.getPosition().x;
								playerToBoundary.y = (float)testY + j - m_player.getPosition().y;
								float d = playerToBoundary.magnitude();
								float dotProduct = dot(eye, playerToBoundary);
								float dot = (eye.x * playerToBoundary.x / d) + (eye.y * playerToBoundary.y / d);
								p.push_back(std::make_pair(d, dot));
							}
						}
						std::sort(p.begin(), p.end(),
							[](const std::pair<float, float>& a, const std::pair<float, float>& b) {return a.first < b.first; });

						float boundaryWindow = 0.001f;
						if (acosf(p[0].second) < boundaryWindow) boundary = true;
						if (acosf(p[1].second) < boundaryWindow) boundary = true;
					}
				}
			}
		}

		int ceiling = (int)((m_windowHeight / 2.0f) - m_windowHeight / distanceToWall);
		int floor = m_windowHeight - ceiling;

		// Draw walls
		// Choose wall colour based on distance to player
		Uint8 wallShade = 0;
		if (distanceToWall < m_maxRayDepth && !boundary)
			wallShade = (Uint8)(255.0f * (1.0f - distanceToWall / m_maxRayDepth));
		SDL_Rect r{ x * m_colWidth, ceiling, m_colWidth, floor - ceiling };
		SDL_SetRenderDrawColor(m_renderer, 0, 0, wallShade, 255);
		SDL_RenderFillRect(m_renderer, &r);
	}

	//m_map.drawMinimap(m_renderer, m_player.getPosition());

	m_player.draw(m_renderer, m_windowWidth, m_windowHeight);

	SDL_RenderPresent(m_renderer);
}

void RayCastDemo::setup()
{
	m_map.loadFromFile("maps/test.csv");
	std::unique_ptr<Texture> sprite(new Texture("sprites/Backstab128/Back01.png", m_renderer));
	m_player.setSprite(std::move(sprite));
}
