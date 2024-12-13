#include "math/Vector2.hpp"

Vector2::Vector2(int x, int y) : x(x), y(y) {};
Vector2::Vector2(float x, float y) : x(x), y(y) {};
Vector2::Vector2() : x(0), y(0) {};
Vector2::Vector2(const Vector2 &v) : x(v.x), y(v.y) {};
Vector2::Vector2(double x, double y) : x(x), y(y) {};

float Vector2::getX() const { return x; }
float Vector2::getY() const { return y; }

Vector2 &Vector2::operator=(const Vector2 &v) {
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2 &v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const Vector2 &v) const {
	return Vector2(x * v.x, y * v.y);
}

float Vector2::dot(const Vector2 &v) const {
	return x * v.x + y * v.y;
}

Vector2::~Vector2() {}
