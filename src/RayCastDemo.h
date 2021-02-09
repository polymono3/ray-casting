#pragma once
#include "SimpleGameEngine.h"
#include "Player.h"
#include "Map.h"

class RayCastDemo : public SimpleGameEngine
{
public:
	RayCastDemo(int windowWidth, int windowHeight, int rows, int columns);

	void handleEvents() override;
	void logic(float deltaTime) override;
	void render() override;

private:
	void setup() override;

	int m_numRows;
	int m_numCols;
	int m_rowHeight;
	int m_colWidth;
	bool m_showBoundaries;
	float m_fov;
	float m_lookSensitivity;
	float m_maxRayDepth;
	float m_rayInterval;
	Player m_player;
	Map m_map;
};