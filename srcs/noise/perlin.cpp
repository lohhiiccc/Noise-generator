
#include <cmath>
#include <algorithm>
#include <random>
#include "noise/perlin.hpp"



PerlinNoise::PerlinNoise() {
    initializeGradients();
}

void PerlinNoise::initializeGradients() {
    std::mt19937 gen(0);
    std::uniform_real_distribution<float> dis(0.0, 2 * M_PI);

    for (int i = 0; i < 256; ++i) {
        float angle = dis(gen);
        grad[i] = Vector2(cos(angle), sin(angle));
    }
}

Vector2 PerlinNoise::randoGradient(int ix, int iy) {
    uint32_t hash = ix * 7385451 ^ iy * 19349663;
    return grad[hash & 0xFF];
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {
    Vector2 gradient = randoGradient(ix, iy);
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    return dx * gradient.getX() + dy * gradient.getY();
}

float PerlinNoise::interpolate(float a, float a1, float w) {
    return (a1 - a) * (3.0 - w * 2.0) * w * w + a;
}

float PerlinNoise::noise(float x, float y) {
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    return interpolate(ix0, ix1, sy);
}
