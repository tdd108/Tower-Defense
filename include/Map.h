#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 28
#define MAP_HEIGHT 22
#define CELL_SIZE 40
#define GRID_LOWER_LIMIT 2

#define MIN_PATH_LENGTH 75
#define MIN_PATH_TURN 8

#define MAP_OFFSET_x 70
#define MAP_OFFSET_y 50

#define VECTOR_UP {0, -1}
#define VECTOR_DOWN {0, 1}
#define VECTOR_RIGHT {1, 0}
#define VECTOR_LEFT {-1, 0}

#include <MLV/MLV_all.h>

#include "utils.h"
#include "Cell.h"

/**
 * @brief Map data.
 * @param monsterNest cell which is monster nest.
 * @param playerCamp cell which is player camp.
 * @param pathlength the length of the path on which monsters can walk.
 * @param numTurn the number of turn of path (used for segment division).
 * @param grid 2d array that contains all the cells of the map.
 */
typedef struct map {
    Cell monsterNest; Cell playerCamp;
    int pathlength; int numTurn;
    Cell *path; 
    Cell grid[MAP_HEIGHT][MAP_WIDTH];
} Map;

/**
 * @brief Initializes the map with default settings.
 * 
 * @param map Pointer to the Map struct to be initialized
 * 
 */
void initializeMap(Map *map);

/**
 * @brief Generates the map, including paths and other elements.
 * 
 * @param map Pointer to the Map struct to be generated
 */
void generateMap();

/**
 * @brief Checks if a cell is within the boundaries of the map grid.
 * 
 * @param cell The cell to check
 * @return int Returns 1 if the cell is within the grid, otherwise 0
 */
int withinGrid(Cell cell);

/**
 * @brief Checks if the current cell has a path neighbor in the given direction.
 * 
 * @param currentCell The current cell being checked
 * @param map The map containing the grid and paths
 * @param vector The direction to check for path neighbors
 * @return int Returns 1 if there is a path neighbor in the direction, otherwise 0
 */
int hasPathNeighbor(Cell currentCell, Map map, Vector vector);

/**
 * @brief Calculates the distance in a specified direction until a path neighbor is found.
 * 
 * @param current The current cell to start the calculation
 * @param map The map containing the grid and paths
 * @param vec The direction vector to calculate distance
 * @return int The distance in the specified direction until a path neighbor is found
 */
int calcExtend(Cell current, Map map, Vector vec);

/**
 * @brief Extend the path in the current direction.
 * 
 * @param currentCell The current cell to start the extension.
 * @param currentDir The current direction to extend.
 * @param step Number of step to extend.
 * @param map The map containing the grid and paths.
 * @return int The distance in the specified direction until a path neighbor is found
 */
void extendPath(Cell *currentCell, Vector currentDir, int step, Map *map);

#endif