#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "utils.h"

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

float getRandomFloat(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

int calculateRandomSum(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += (rand() < RAND_MAX * 0.75) ? 1 : 0;;
    }
    return sum;
}

int chooseRandomDirection(int extents[], int totalExtent) {
    int randomNum = getRandomNumber(0, totalExtent);
    int dirIndex;
    for (dirIndex = 0; dirIndex < 4; dirIndex++) {
        if (randomNum < extents[dirIndex])
            break;
        randomNum -= extents[dirIndex];
    }
    return dirIndex;
}

MLV_Color hueToRgb(int hue) {
    float h = (float)hue / 360.0; // Normalize hue to the range [0, 1]

    float r, g, b;
    const float saturation = 1.0; // Full saturation for simplicity
    const float brightness = 1.0; // Full brightness for simplicity

    int i;
    float f, p, q, t;

    if (saturation == 0) {
        r = g = b = brightness; // If saturation is 0, it's a shade of gray
    } else {
        h *= 6; // Hue is in the range [0, 6]
        i = (int)h;
        f = h - i;
        p = brightness * (1 - saturation);
        q = brightness * (1 - saturation * f);
        t = brightness * (1 - saturation * (1 - f));

        switch (i) {
            case 0: r = brightness; g = t; b = p; break;
            case 1: r = q; g = brightness; b = p; break;
            case 2: r = p; g = brightness; b = t; break;
            case 3: r = p; g = q; b = brightness; break;
            case 4: r = t; g = p; b = brightness; break;
            default: r = brightness; g = p; b = q; break;
        }
    }

    // Scale RGB values to the range [0, 255]
    MLV_Color color = MLV_rgba((int)(r * 255), (int)(g * 255), (int)(b * 255), 255);

    return color;
}