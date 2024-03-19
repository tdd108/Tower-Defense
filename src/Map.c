#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Map.h"

void initializeMap(Map *map) {
    //malloc the path of map
    map->pathlength = 1;
    map->path = (Cell*)malloc(sizeof(Cell));
    if (map->path == NULL) {
        free(map->path);
        printf("malloc failed.\n");
        return;
    }

    //set all cell of map to empty
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map->grid[i][j].x = j;
            map->grid[i][j].y = i;
            map->grid[i][j].type = EMPTY;
            map->grid[i][j].center = centerPosition(j, i);
            map->grid[i][j].center.x += MAP_OFFSET_x;
            map->grid[i][j].center.y += MAP_OFFSET_y;
        }
    }

    map->numTurn = 0;

    //Choose Monsters's nest
    int xNest = getRandomNumber(2, MAP_WIDTH - 3);
    int yNest = getRandomNumber(2, MAP_HEIGHT - 3);
    map->grid[yNest][xNest].type = NEST;
    map->monsterNest = map->grid[yNest][xNest];
    map->path[0] = map->monsterNest;
}

int hasPathNeighbor(Cell currentCell, Map map, Vector vector) {
    int x = currentCell.x;
    int y = currentCell.y;

    if (vector.y == 0) {
        int right1 = map.grid[y - 1][x + vector.x].type;
        int right2 = map.grid[y][x + 2 * vector.x].type;
        int right3 = map.grid[y + 1][x + vector.x].type;
        int above = map.grid[y - 2][x].type;
        int below = map.grid[y + 2][x].type;
        
        return (right1 != EMPTY || right2 != EMPTY || right3 != EMPTY || above != EMPTY || below != EMPTY);
    }

    if (vector.x == 0) {
        int below1 = map.grid[y + vector.y][x - 1].type;
        int below2 = map.grid[y + vector.y][x + 1].type;
        int below3 = map.grid[y + 2 * vector.y][x].type;
        int left = map.grid[y][x - 2].type;
        int right = map.grid[y][x + 2].type;
        
        return (below1 != EMPTY || below2 != EMPTY || below3 != EMPTY || left != EMPTY || right != EMPTY);
    }

    return 0;
}

int withinGrid(Cell cell) {
    return (cell.y >= GRID_LOWER_LIMIT && 
            cell.y < MAP_HEIGHT - GRID_LOWER_LIMIT && 
            cell.x >= GRID_LOWER_LIMIT && 
            cell.x < MAP_WIDTH - GRID_LOWER_LIMIT);
}

int calcExtend(Cell current, Map map, Vector vec) {
    int extent = 0;
    Cell nextCell = newCell(current.x + vec.x, current.y + vec.y, EMPTY);
    while ((withinGrid(nextCell) && !hasPathNeighbor(nextCell, map, vec))) {
        extent++;
        nextCell.y += vec.y;
        nextCell.x += vec.x;
    }
    return extent;
}

void extendPath(Cell *currentCell, Vector currentDir, int step, Map *map) {
    int newLength = step + map->pathlength;
    Cell *temp = realloc(map->path, newLength * sizeof(Cell));
    if (temp == NULL) {
        free(map->path);
        map->path = NULL;
        printf("realloc failed.\n");
        return;
    } else {
        map->path = temp;
    }

    int x = currentCell->x + currentDir.x;
    int y = currentCell->y + currentDir.y;
    Cell nextCell = newCell(x, y, PATH);
    for (int i = 0; i < step; i++) {
        if (0 < x && x < MAP_WIDTH && 0 < y && y < MAP_HEIGHT) {
            if (i < step - 1)
                map->grid[y][x].type = PATH;
            else
                map->grid[y][x].type = TURN;

            map->path[map->pathlength] = map->grid[y][x];
            map->pathlength++;
        }
        *currentCell = nextCell;
        x = currentCell->x  + currentDir.x;
        y = currentCell->y + currentDir.y;
        nextCell = newCell(x, y, PATH);
    }
}

void generateMap(Map *map) {
    Vector directions[4] = {VECTOR_UP, VECTOR_DOWN, VECTOR_RIGHT, VECTOR_LEFT};
    int extents[4] = {0};
    int totalExtent = 0;
    Direction currentDir = -1;
    Cell current;


    initializeMap(map);
    current = (*map).monsterNest;

    
    while (1) {
        for (int i = 0; i < 4; i++) {
            extents[i] = calcExtend(current, *map, directions[i]);
        }
        
        if (currentDir == UP || currentDir == DOWN) {
            extents[UP] = 0;
            extents[DOWN] = 0;
        }
        else if (currentDir == LEFT || currentDir == RIGHT) {
            extents[LEFT] = 0;
            extents[RIGHT] = 0;
        }

        totalExtent = extents[UP] + extents[DOWN] + extents[RIGHT] + extents[LEFT];
        
        if (totalExtent != 0)
            currentDir = chooseRandomDirection(extents, totalExtent);

        if (extents[currentDir] <= 2) {
            if (map->pathlength >= MIN_PATH_LENGTH && map->numTurn >= MIN_PATH_TURN)
                break;
            map->numTurn = 0;
            currentDir = -1;
            free(map->path);
            map->path = NULL;
            initializeMap(map);
            current = (*map).monsterNest;
        }
        else {
            int s = calculateRandomSum(extents[currentDir]);
            int step = (s >= 3) ? s : 3; //Determine Max Step
            extendPath(&current, directions[currentDir], step, map);
            map->numTurn++;
            totalExtent = 0;
        }
    }
    
    map->grid[current.y][current.x].type = CAMP;
    map->playerCamp = map->grid[current.y][current.x];
    map->path[map->pathlength - 1] = map->playerCamp;
}