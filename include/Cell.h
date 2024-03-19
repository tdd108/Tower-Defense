#ifndef CELL_H
#define CELL_H

#include "Position.h"

// Enum defining different types of MapCells
typedef enum {
    EMPTY,
    PATH,
    TURN,
    NEST,
    CAMP,
    TOWER
} CellType;

// Structure representing a kap Cell
typedef struct cell{
    int x; int y;
    Position center;
    CellType type;
} Cell;

/**
 * @brief Creates a new cell with specified coordinates and type.
 * 
 * @param x X-coordinate of the cell
 * @param y Y-coordinate of the cell
 * @param type Type of the cell (e.g., EMPTY, PATH, NEST, etc.)
 * @return Cell The created cell with provided coordinates and type
 */
Cell newCell(int x, int y, CellType type);

#endif