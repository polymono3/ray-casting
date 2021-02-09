#pragma once
#include "Vec2f.h"
#include <math.h>
#include <stdint.h>
#include <memory>
#include <utility>

class Map;
class Texture;
struct SDL_Renderer;

class Player
{
public:
	Player(float x, float y);
	Player(const Vec2f& position);

	void processKeyboard(const uint8_t* keyState);
	void update(float deltaTime, const Map& map);
	void draw(SDL_Renderer* renderer, int windowWidth, int windowHeight);

	Vec2f getForward() const { return Vec2f(sinf(m_viewAngle), cosf(m_viewAngle)); }
	Vec2f getPosition() const { return m_position; }
	float getViewAngle() const { return m_viewAngle; }
	void setPosition(const Vec2f& position) { m_position = position; }
	void setSprite(std::unique_ptr<Texture>&& sprite) { m_sprite = std::move(sprite); }

private:
	Vec2f m_position;
	float m_viewAngle;
	float m_speed;
	float m_angularSpeed;
	std::unique_ptr<Texture> m_sprite;
};