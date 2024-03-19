#ifndef POSITION_H
#define POSITION_H

#define CELL_SIZE 40

// Enum defining different direction
typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
} Direction;

typedef struct postion {
    int x;
    int y;
} Position;

typedef Position Vector;

Position newPosition(int x, int y);

Position centerPosition(int x, int y);

float distance(Position posA, Position posB);

#endif