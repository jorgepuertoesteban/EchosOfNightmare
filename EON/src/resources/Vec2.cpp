
#include "Vec2.h"

Vec2::Vec2() :x(0), y(0) {}
Vec2::Vec2(float x, float y):x(x),y(y){}
Vec2::~Vec2(){}
Vec2 Vec2::operator+(const Vec2& other) {
	float x = this->x + other.x;
	float y = this->y + other.y;
	return Vec2(x,y);
}
Vec2 Vec2::operator-(const Vec2& other) {
	float x = this->x - other.x;
	float y = this->y - other.y;
	return Vec2(x, y);
}
Vec2 Vec2::operator*(const Vec2& other) {
	float x = this->x * other.x;
	float y = this->y * other.y;
	return Vec2(x, y);
}
Vec2 Vec2::operator/(const Vec2& other) {
	float x = this->x / other.x;
	float y = this->y / other.y;
	return Vec2(x, y);
}
Vec2 Vec2::operator*(const int other) {
	return Vec2(x*other, y*other);
}
Vec2 Vec2::operator/(const int other) {
	return Vec2(x/other, y/other);
}