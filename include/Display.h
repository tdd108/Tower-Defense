#ifndef DISPLAY_H
#define DISPLAY_H

#define LEFT_SIDE_BAR 70
#define RIGHT_SIDE_BAR 200
#define TOP_SIDE_BAR 50
#define BOTTOM_SIDE_BAR 30

#define MAP_OFFSET_X LEFT_SIDE_BAR
#define MAP_OFFSET_Y TOP_SIDE_BAR

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

#define WINDOW_WIDTH CELL_SIZE * MAP_WIDTH + LEFT_SIDE_BAR + RIGHT_SIDE_BAR
#define WINDOW_HEIGHT CELL_SIZE * MAP_HEIGHT + TOP_SIDE_BAR + BOTTOM_SIDE_BAR

#define HP_BAR_WIDTH 15.0
#define HP_BAR_HEIGHT 3

#define emptyColor MLV_COLOR_DARK_GREEN
#define pathColor MLV_COLOR_WHITE
#define nestColor MLV_COLOR_RED
#define campColor MLV_COLOR_GREEN

typedef enum {
    DIS_SPLASH,
    DIS_POISON,
    DIS_SLOW,
    DIS_NONE,
} DisplayMonsterEff;

#include <MLV/MLV_all.h>
#include "Monster.h"
#include "Tower.h"
#include "Input.h"

//Function to initialize windows, load image...
void startWindow();

void displayFillScreen();

//Function to display the map
void displayMap(Map map);

void displayHPBar(int x, int y, Monster monster);

void displayMonster(Monster monster);

void displayWave(Wave wave);

void displayTower(Tower tower);

void displayListTower(ListTowers list);

void displayWave(Wave wave);

void displayWaves(int numWave, Wave *waves);

void displayCell(int x, int y, MLV_Color color);

void clearPath(Map map);

void displayProjectile(Projectile projectile);

void displayListProjectile(ListProjectile listProjectile);

void displayGridOption();

void displayGemGrid(CursorState state);

void displayGem(Gem gem);

void displayListGem(ListGem list);

void displayManaBar(double manaCur, double manaMax);

void displayTime(double time);

void displayNumWave(int wave, int totalWave);

void displayMessage();

//Function to close windows, free image...
void endWindow();

#endif