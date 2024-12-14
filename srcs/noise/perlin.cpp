
#include <cmath>
#include <algorithm>
#include <random>
#include "noise/perlin.hpp"



PerlinNoise::PerlinNoise() : seed(0) {
    initializeGradients();
}

PerlinNoise::PerlinNoise(int seed) : seed(seed) {
	initializeGradients();
}

void PerlinNoise::initializeGradients() {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(0.0, 2 * M_PI);

    for (int i = 0; i < 512; ++i) {
        float angle = dis(gen);
        grad[i] = Vector2(cos(angle), sin(angle));
    }
}

Vector2 PerlinNoise::randoGradient(int ix, int iy) {
    uint32_t hash = ix * 7385451 ^ iy * 19349663;
    return grad[hash & 512];
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {
    Vector2 gradient = randoGradient(ix, iy);
	Vector2 d(x - (float)ix, y - (float)iy);
    return d.getX() * gradient.getX() + d.getY() * gradient.getY();
}

float PerlinNoise::interpolate(float a, float a1, float w) {
    return (a1 - a) * (3.0 - w * 2.0) * w * w + a;
}

float PerlinNoise::noise(float x, float y) {
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

	Vector2 s(x - (float)x0, y - (float)y0);
	Vector2 n(dotGridGradient(x0, y0, x, y), dotGridGradient(x1, y0, x, y));

    float ix0 = interpolate(n.getX(), n.getY(), s.getX());

	n = Vector2(dotGridGradient(x0, y1, x, y), dotGridGradient(x1, y1, x, y));
    float ix1 = interpolate(n.getX(), n.getY(), s.getX());

    return interpolate(ix0, ix1, s.getY());
}
