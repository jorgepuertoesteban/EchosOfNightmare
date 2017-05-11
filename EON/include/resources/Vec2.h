#pragma once

class Vec2 {
public:
	Vec2();
	Vec2(float x, float y);
	~Vec2();
	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);
	Vec2 operator+(const Vec2& other);
	Vec2 operator-(const Vec2& other);
	Vec2 operator*(const Vec2& other);
	Vec2 operator/(const Vec2& other);
	Vec2 operator*(const int other);
	Vec2 operator/(const int other);
	float x;
	float y;
};