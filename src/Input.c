#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "Input.h"

MouseCursor newCursor() {
    MouseCursor newCursor;
    newCursor.gem = NULL;
    newCursor.state = NONE;
    newCursor.option = OPTION_NONE;
    newCursor.leftMouseLastState = MLV_RELEASED;
    return newCursor;
}

void getGemCursor(MouseCursor *cursor, Gem* listGemUnSet[][3]) {
    if (GEM_GRID_X_1 > cursor->pos.x || GEM_GRID_X_2 < cursor->pos.x ||
        GEM_GRID_Y_1 > cursor->pos.y || GEM_GRID_Y_2 < cursor->pos.y) {
        cursor->option = OPTION_NONE;
        cursor->state = NONE;
        return;
    }

    int x = (cursor->pos.x - GEM_GRID_X_1) / CELL_SIZE;
    int y = (cursor->pos.y - GEM_GRID_Y_1) / CELL_SIZE;

    if (listGemUnSet[y][x] == NULL) {
        cursor->option = OPTION_NONE;
        cursor->state = NONE;
        return;
    }
    cursor->gemLastPos = listGemUnSet[y][x]->center;
    cursor->gem = listGemUnSet[y][x];
    cursor->state = HAS_GEM;
    printf("has_gem\n");
}

void inputHandler(MouseCursor *cursor) {
    int x, y;

    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
        cursor->leftMouseLastState = MLV_RELEASED;
        cursor->state = NONE;
        if (cursor->gem != NULL) {
            if (cursor->option == OPTION_6) {
                cursor->state = CHECK_GEM;
                return;
            }
            cursor->state = CHECK_TOWER;
            return;
        }
    }

    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_PRESSED) {
        return;
    }

    MLV_get_mouse_position(&x, &y);

    if (cursor->state == HAS_GEM && cursor->gem != NULL) {
        cursor->gem->x = x;
        cursor->gem->y = y;
        cursor->gem->center.x = x;
        cursor->gem->center.y = y;
        return;
    }

    if (cursor->option == OPTION_NONE) {
        cursor->state = NONE;
        if (OPTION_BUTTON_1_X_1 < x && x < OPTION_BUTTON_1_X_2 &&
            OPTION_BUTTON_1_Y_1 < y && y < OPTION_BUTTON_1_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_1;
            return;
        }

        if (OPTION_BUTTON_2_X_1 < x && x < OPTION_BUTTON_2_X_2 &&
            OPTION_BUTTON_2_Y_1 < y && y < OPTION_BUTTON_2_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_2;
            return;
        }

        if (OPTION_BUTTON_3_X_1 < x && x < OPTION_BUTTON_3_X_2 &&
            OPTION_BUTTON_3_Y_1 < y && y < OPTION_BUTTON_3_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_3;
            return;
        }

        if (OPTION_BUTTON_4_X_1 < x && x < OPTION_BUTTON_4_X_2 &&
            OPTION_BUTTON_4_Y_1 < y && y < OPTION_BUTTON_4_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_4;
            return;
        }

        if (OPTION_BUTTON_5_X_1 < x && x < OPTION_BUTTON_5_X_2 &&
            OPTION_BUTTON_5_Y_1 < y && y < OPTION_BUTTON_5_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_5;
            return;
        }

        if (OPTION_BUTTON_6_X_1 < x && x < OPTION_BUTTON_6_X_2 &&
            OPTION_BUTTON_6_Y_1 < y && y < OPTION_BUTTON_6_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->option = OPTION_6;
            return;
        }
        if (GEM_GRID_X_1 < x && x < GEM_GRID_X_2 &&
            GEM_GRID_Y_1 < y && y < GEM_GRID_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
            cursor->leftMouseLastState = MLV_PRESSED;
            cursor->pos.x = x;
            cursor->pos.y = y;
            cursor->state = DRAG_GEM;
            return;
        }
    }
    else {
        if (cursor->option == OPTION_3) {
            if (MAP_X_1 < x && x < MAP_X_2 &&
            MAP_Y_1 < y && y < MAP_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
                cursor->leftMouseLastState = MLV_PRESSED;
                x = (x - MAP_OFFSET_X) / CELL_SIZE;
                y = (y - MAP_OFFSET_Y) / CELL_SIZE;
                cursor->pos.x = x;
                cursor->pos.y = y;
                cursor->state = PLACE_TOWER;
                cursor->option = OPTION_NONE;
                return;
            } else if ((MAP_X_1 > x || x > MAP_X_2 ||
            MAP_Y_1 > y || y > MAP_Y_2) && cursor->leftMouseLastState == MLV_RELEASED) {
                cursor->state = NONE;
                cursor->option = OPTION_NONE;
            }
        }
        // if (cursor->option == OPTION_3 && MAP_X_1 < x && x < MAP_X_2 &&
        //     MAP_Y_1 < y && y < MAP_Y_2 && cursor->leftMouseLastState == MLV_RELEASED) {
        //     cursor->leftMouseLastState = MLV_PRESSED;
        //     x = (x - MAP_OFFSET_X) / CELL_SIZE;
        //     y = (y - MAP_OFFSET_Y) / CELL_SIZE;
        //     cursor->pos.x = x;
        //     cursor->pos.y = y;
        //     cursor->state = PLACE_TOWER;
        //     cursor->option = OPTION_NONE;
        //     return;
        // }
        else if (cursor->option == OPTION_5) { 
            if (GEM_BUTTON_LV1_X_1 < x && x < GEM_BUTTON_LV1_X_2 && GEM_BUTTON_LV1_Y_1 < y && y < GEM_BUTTON_LV1_Y_2) {
                cursor->level = 1;
                cursor->state = ADD_GEM;
                cursor->option = OPTION_NONE;
            }
            else if (GEM_BUTTON_LV2_X_1 < x && x < GEM_BUTTON_LV2_X_2 && GEM_BUTTON_LV2_Y_1 < y && y < GEM_BUTTON_LV2_Y_2){
                cursor->level = 2;
                cursor->state = ADD_GEM;
                cursor->option = OPTION_NONE;
            }
            else if (GEM_BUTTON_LV3_X_1 < x && x < GEM_BUTTON_LV3_X_2 && GEM_BUTTON_LV3_Y_1 < y && y < GEM_BUTTON_LV3_Y_2){
                cursor->level = 3;
                cursor->state = ADD_GEM;
                cursor->option = OPTION_NONE;
            }
            
        }
        else if (cursor->option == OPTION_6 && GEM_GRID_X_1 < x && x < GEM_GRID_X_2 &&
            GEM_GRID_Y_1 < y && y < GEM_GRID_Y_2) {
            cursor->pos.x = x;
            cursor->pos.y = y;
            cursor->state = DRAG_GEM;
        }
    }
}