#include "Player.h"
#include <math.h>
#include <SDL.h>
#include "Map.h"
#include "Texture.h"

const float MOVEMENT_SPEED = 5.0f;
const float ANGULAR_SPEED = 2.0f;

Player::Player(float x, float y) :
	m_position(x, y),
	m_viewAngle(0.0f),
	m_speed(0.0f),
	m_angularSpeed(0.0f)
{
}

Player::Player(const Vec2f& position) :
	m_position(position),
	m_viewAngle(0.0f),
	m_speed(0.0f),
	m_angularSpeed(0.0f)
{
}

void Player::processKeyboard(const uint8_t* keyState)
{
	m_speed = 0.0f;
	m_angularSpeed = 0.0f;

	if (keyState[SDL_SCANCODE_A])
		m_angularSpeed -= ANGULAR_SPEED;
	if (keyState[SDL_SCANCODE_D])
		m_angularSpeed += ANGULAR_SPEED;
	if (keyState[SDL_SCANCODE_W])
		m_speed += MOVEMENT_SPEED;
	if (keyState[SDL_SCANCODE_S])
		m_speed -= MOVEMENT_SPEED;
}

void Player::update(float deltaTime, const Map& map)
{
	m_viewAngle += m_angularSpeed * deltaTime;
	m_position += getForward() * m_speed * deltaTime;
	int row = static_cast<int>(m_position.x);
	int col = static_cast<int>(m_position.y);
	if (map.getCell(row, col) == 1)
		m_position -= getForward() * m_speed * deltaTime;
}

void Player::draw(SDL_Renderer* renderer, int windowWidth, int windowHeight)
{
	m_sprite->render(renderer, windowWidth / 2, windowHeight - m_sprite->getHeight() / 2);
}
