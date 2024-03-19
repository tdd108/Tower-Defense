#ifndef UTILS_H
#define UTILS_H

int getRandomNumber(int min, int max);

float getRandomFloat(float min, float max);

// Function to calculate the sum of 'n' random values
int calculateRandomSum(int n);

int chooseRandomDirection(int extents[], int totalExtent);

MLV_Color hueToRgb(int hue);

#endif