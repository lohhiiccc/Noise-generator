#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
public:
	Vector2(int x, int y);
	Vector2(float x, float y);
	Vector2(double x, double y);
	Vector2();
	Vector2(const Vector2 &v);

	~Vector2();

	Vector2 &operator=(const Vector2 &v);
	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator*(const Vector2 &v) const;

	float dot(const Vector2 &v) const;

	float getX() const;
	float getY() const;
private:
	double x;
	double y;
};

#endif
