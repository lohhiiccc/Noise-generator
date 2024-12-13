
#ifndef PERLIN_HPP
#define PERLIN_HPP
#include "math/Vector2.hpp"


class PerlinNoise {
public:
	PerlinNoise();
	float  noise(float x, float  y);

private:
	void initializeGradients();
	Vector2 grad[512];
	Vector2 randoGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float interpolate(float a, float a1, float w);
};

#endif