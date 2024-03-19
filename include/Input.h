#ifndef INPUT_H
#define INPUT_H

#define MAP_X_1 70
#define MAP_Y_1 50
#define MAP_X_2 1190
#define MAP_Y_2 930

#define OPTION_BUTTON_1_X_1 1224
#define OPTION_BUTTON_1_Y_1 70
#define OPTION_BUTTON_1_X_2 1284
#define OPTION_BUTTON_1_Y_2 136

#define OPTION_BUTTON_2_X_1 1285
#define OPTION_BUTTON_2_Y_1 70
#define OPTION_BUTTON_2_X_2 1351
#define OPTION_BUTTON_2_Y_2 136

#define OPTION_BUTTON_3_X_1 1224
#define OPTION_BUTTON_3_Y_1 136
#define OPTION_BUTTON_3_X_2 1284
#define OPTION_BUTTON_3_Y_2 202

#define OPTION_BUTTON_4_X_1 1285
#define OPTION_BUTTON_4_Y_1 136
#define OPTION_BUTTON_4_X_2 1351
#define OPTION_BUTTON_4_Y_2 202

#define OPTION_BUTTON_5_X_1 1224
#define OPTION_BUTTON_5_Y_1 202
#define OPTION_BUTTON_5_X_2 1284
#define OPTION_BUTTON_5_Y_2 268

#define OPTION_BUTTON_6_X_1 1285
#define OPTION_BUTTON_6_Y_1 202
#define OPTION_BUTTON_6_X_2 1351
#define OPTION_BUTTON_6_Y_2 268

#define GEM_BUTTON_LV1_X_1 1180
#define GEM_BUTTON_LV1_Y_1 290
#define GEM_BUTTON_LV1_X_2 1231
#define GEM_BUTTON_LV1_Y_2 450

#define GEM_BUTTON_LV2_X_1 1180
#define GEM_BUTTON_LV2_Y_1 450
#define GEM_BUTTON_LV2_X_2 1231
#define GEM_BUTTON_LV2_Y_2 610

#define GEM_BUTTON_LV3_X_1 1180
#define GEM_BUTTON_LV3_Y_1 610
#define GEM_BUTTON_LV3_X_2 1231
#define GEM_BUTTON_LV3_Y_2 770

#define GEM_GRID_X_1 1230
#define GEM_GRID_Y_1 290
#define GEM_GRID_X_2 1350
#define GEM_GRID_Y_2 770

#define LEFT_SIDE_BAR 70
#define RIGHT_SIDE_BAR 200
#define TOP_SIDE_BAR 50
#define BOTTOM_SIDE_BAR 30

#define MAP_OFFSET_X LEFT_SIDE_BAR
#define MAP_OFFSET_Y TOP_SIDE_BAR

#include "Tower.h"
#include "Gem.h"
#include "Position.h"

typedef enum {
    OPTION_1,
    OPTION_2,
    OPTION_3,
    OPTION_4,
    OPTION_5,
    OPTION_6,
    OPTION_NONE,
} CursorOption;

typedef enum {
    PLACE_TOWER,
    CHOOSE_OPTION,
    DRAG_GEM,
    HAS_GEM,
    CHECK_TOWER,
    CHECK_GEM,
    ADD_GEM,
    NONE,
} CursorState;

typedef struct mousecursor {
    Position pos;
    CursorState state;
    CursorOption option;
    MLV_Button_state leftMouseLastState;
    Position gemLastPos;
    Gem *gem;
    int level;
} MouseCursor;

MouseCursor newCursor();

void inputHandler(MouseCursor *cursor);

void getGemCursor(MouseCursor *cursor, Gem* listGemUnSet[][3]);

#endif