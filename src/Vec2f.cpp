#include "Vec2f.h"
#include <math.h>

Vec2f& Vec2f::operator+=(const Vec2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2f& Vec2f::operator-=(const Vec2f& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2f& Vec2f::operator*=(float a)
{
	x *= a;
	y *= a;
	return *this;
}

float Vec2f::magnitude() const
{
	return sqrtf(x * x + y * y);
}

void Vec2f::normalize()
{
	(*this) *= 1 / magnitude();
}
