#pragma once

class Vec2f
{
public:
	float x;
	float y;

	Vec2f(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {}

	Vec2f& operator+=(const Vec2f& rhs);
	Vec2f& operator-=(const Vec2f& rhs);
	Vec2f& operator*=(float a);

	float magnitude() const;
	void normalize();
};

inline float dot(const Vec2f& a, const Vec2f& b)
{
	return a.x * b.x + a.y * b.y;
}

inline Vec2f operator*(const Vec2f& a, float b)
{
	Vec2f temp = a;
	temp.x *= b;
	temp.y *= b;
	return temp;
}