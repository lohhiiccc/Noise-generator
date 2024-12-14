
#ifndef PERLIN_HPP
#define PERLIN_HPP
#include "math/Vector2.hpp"


class PerlinNoise {
public:
	PerlinNoise();
	PerlinNoise(int seed);
	float  noise(float x, float  y);

private:
	int seed;
	void initializeGradients();
	Vector2 grad[256];
	Vector2 randoGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float interpolate(float a, float a1, float w);
};

#endif