#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Cell.h"

Cell newCell(int x, int y, CellType type) {
    Cell newCell;
    newCell.x = x;
    newCell.y = y;
    newCell.type = type;
    return newCell;
}