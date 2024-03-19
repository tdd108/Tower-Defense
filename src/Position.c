#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Position.h"

Position newPosition(int x, int y) {
    Position newPosition;
    newPosition.x = x;
    newPosition.y = y;
    return newPosition;
}

Position centerPosition(int x, int y) {
    Position newPosition;
    newPosition.x = x * CELL_SIZE + CELL_SIZE / 2;
    newPosition.y = y * CELL_SIZE + CELL_SIZE / 2;
    return newPosition;
}

float distance(Position posA, Position posB) {
    return sqrt((posA.x - posB.x) * (posA.x - posB.x) +
                (posA.y - posB.y) * (posA.y - posB.y));
}