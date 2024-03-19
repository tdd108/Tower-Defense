#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

void startWindow() {
    MLV_create_window("Tower Defense", "Tower Defense", WINDOW_WIDTH, WINDOW_HEIGHT);
    // MLV_enable_full_screen();
}

void endWindow() {
    MLV_free_window();
}

void displayFillScreen() {
    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, MLV_COLOR_GRAY);
}

void displayHPBar(int x, int y, Monster monster) {
    MLV_draw_rectangle(x, y, HP_BAR_WIDTH, HP_BAR_HEIGHT, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(x, y + 1, HP_BAR_WIDTH / monster.initialHP * monster.hp, HP_BAR_HEIGHT - 2, MLV_COLOR_GREEN);
}

void displayMonster(Monster monster) {
    MLV_draw_filled_circle(monster.x, monster.y, MONSTER_SIZE, monster.color);
    displayHPBar(monster.x - 7, monster.y - 13, monster);
}

void displayWave(Wave wave) {
    Node *node;
    Monster *monster;
    for (node = wave.monsters.head; node != NULL; node = node->next) {
        monster = (Monster*)(node->data);
        if (monster->hp > 0)
            displayMonster(*monster);
        if (monster->effect == EFF_SPLASH)
            MLV_draw_text(monster->x - 20, monster->y - 30, "Splash", MLV_COLOR_RED);
        if (monster->effect == EFF_SLOW)
            MLV_draw_text(monster->x - 20, monster->y - 30, "Slow", MLV_COLOR_BLUE);
        if (monster->effect == EFF_POISON)
            MLV_draw_text(monster->x - 20, monster->y - 30, "Poison", MLV_COLOR_GREEN);
        if (monster->effect == EFF_VAPOR)
            MLV_draw_text(monster->x - 20, monster->y - 30, "Vapor", MLV_COLOR_RED);
    }
}

void displayWaves(int numWave, Wave *waves) {
    for (int i = 0; i < numWave; i++) 
        displayWave(waves[i]);
}

void displayTower(Tower tower) {
    MLV_draw_filled_rectangle(MAP_OFFSET_X + tower.x * CELL_SIZE, MAP_OFFSET_Y + tower.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, MLV_COLOR_GRAY10);
    MLV_draw_filled_rectangle(MAP_OFFSET_X + tower.x * CELL_SIZE + 3, MAP_OFFSET_Y + tower.y * CELL_SIZE + 3, CELL_SIZE - 7 , CELL_SIZE -  7, MLV_COLOR_DARK_GRAY);
    MLV_draw_circle(tower.center.x, tower.center.y, tower.range, MLV_COLOR_RED);
}

void displayListTower(ListTowers list) {
    Node *node;
    Tower *tower;
    for (node = list.towers.head; node != NULL; node = node->next) {
        tower = (Tower*)(node->data);
        displayTower(*tower);
    }
}

void displayCell(int x, int y, MLV_Color color) {
    MLV_draw_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(x, y, CELL_SIZE - 1, CELL_SIZE - 1, color);
}

void displayMap(Map map) {
    MLV_Color colors[5] = {emptyColor, pathColor, pathColor, nestColor, campColor};
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int xCell = j * CELL_SIZE;
            int yCell = i * CELL_SIZE;
            int type = map.grid[i][j].type;
            MLV_draw_rectangle(MAP_OFFSET_X + xCell, MAP_OFFSET_Y + yCell, CELL_SIZE, CELL_SIZE, MLV_COLOR_BLACK);
            MLV_draw_filled_rectangle(MAP_OFFSET_X + xCell, MAP_OFFSET_Y + yCell, CELL_SIZE - 1, CELL_SIZE - 1, colors[type]);
        }
    }
}

void displayProjectile(Projectile projectile) {
    MLV_draw_filled_circle(projectile.center.x, projectile.center.y, 4, projectile.color);
}

void displayListProjectile(ListProjectile list) {
    Node *node;
    Projectile *projectile;
    for (node = list.projectiles.head; node != NULL; node = node->next) {
        projectile = (Projectile*)(node->data);
        displayProjectile(*projectile);
    }
}

void displayGridOption() {
    int offsetx = 34;
    int offsety = 20;
    int cellSize = 66;
    int numCol = 2;
    int numRow = 3;
    int x = LEFT_SIDE_BAR + (CELL_SIZE * MAP_WIDTH) + offsetx;
    int y = TOP_SIDE_BAR + offsety;
    MLV_draw_rectangle(x, y, cellSize * numCol, cellSize * numRow, MLV_COLOR_BLACK);
    MLV_draw_line(x + cellSize, y, x + cellSize, y + cellSize * numRow - 1, MLV_COLOR_BLACK);
    MLV_draw_line(x, y + cellSize, x + cellSize * numCol - 1, y + cellSize, MLV_COLOR_BLACK);
    MLV_draw_line(x, y + cellSize * 2, x + cellSize * numCol - 1, y + cellSize * 2, MLV_COLOR_BLACK);

    MLV_draw_text(OPTION_BUTTON_1_X_1 + 15, OPTION_BUTTON_1_Y_2 - 40, "Skip", MLV_COLOR_BLACK);
    MLV_draw_text(OPTION_BUTTON_1_X_1 + 15, OPTION_BUTTON_1_Y_2 - 21, "Wave", MLV_COLOR_BLACK);

    MLV_draw_text(OPTION_BUTTON_2_X_1 + 15, OPTION_BUTTON_2_Y_2 - 40, "Start", MLV_COLOR_BLACK);
    MLV_draw_text(OPTION_BUTTON_2_X_1 + 15, OPTION_BUTTON_2_Y_2 - 21, "Wave", MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(OPTION_BUTTON_3_X_1 + 13, OPTION_BUTTON_3_Y_1 + 0, CELL_SIZE, CELL_SIZE, MLV_COLOR_GRAY10);
    MLV_draw_filled_rectangle(OPTION_BUTTON_3_X_1 + 17, OPTION_BUTTON_3_Y_1 + 4, CELL_SIZE - 8 , CELL_SIZE -  8, MLV_COLOR_DARK_GRAY);
    MLV_draw_text(OPTION_BUTTON_3_X_1, OPTION_BUTTON_3_Y_2 - 25, "Place", MLV_COLOR_BLACK);
    MLV_draw_text(OPTION_BUTTON_3_X_1, OPTION_BUTTON_3_Y_2 -16, "Tower", MLV_COLOR_BLACK);

    MLV_draw_text(OPTION_BUTTON_4_X_1 + 15, OPTION_BUTTON_4_Y_2 - 40, "Increase", MLV_COLOR_BLACK);
    MLV_draw_text(OPTION_BUTTON_4_X_1 + 15, OPTION_BUTTON_4_Y_2 - 15, "Mana", MLV_COLOR_BLACK);

    MLV_draw_filled_circle(OPTION_BUTTON_5_X_1 + 13 + CELL_SIZE / 2, OPTION_BUTTON_5_Y_1 + 0  + CELL_SIZE / 2, CELL_SIZE / 2, MLV_COLOR_BLUE);
    MLV_draw_text(OPTION_BUTTON_5_X_1, OPTION_BUTTON_5_Y_2 - 25, "New Gem", MLV_COLOR_BLACK);

    MLV_draw_filled_circle(OPTION_BUTTON_6_X_1 + 13 + CELL_SIZE / 2, OPTION_BUTTON_6_Y_1 + 0  + CELL_SIZE / 2, CELL_SIZE / 2, MLV_COLOR_BLUE);
    MLV_draw_text(OPTION_BUTTON_6_X_1 + 10, OPTION_BUTTON_6_Y_2 - 25, "Combine", MLV_COLOR_BLACK);
    MLV_draw_text(OPTION_BUTTON_6_X_1 + 10, OPTION_BUTTON_6_Y_2 - 16, "Gem", MLV_COLOR_BLACK);
}

void displayManaBar(double manaCur, double manaMax) {
    int widthBar = 300;
    int heightBar = 30;
    int x = 870;
    int y = 10;
    MLV_draw_rectangle(x, y, widthBar, heightBar, MLV_COLOR_BLACK);
    MLV_draw_filled_rectangle(x, y, manaCur / manaMax * widthBar, heightBar, MLV_COLOR_BLUE);
    MLV_draw_text(x + widthBar / 3, y + heightBar / 3, "%.2f/%.2f", MLV_COLOR_BLACK, manaCur, manaMax);
}

void displayGemGrid(CursorState state) {
    int offsetx = 40;
    int numCol = 3;
    int numRow = 12;
    int x = LEFT_SIDE_BAR + (CELL_SIZE * MAP_WIDTH) + offsetx;
    int y = TOP_SIDE_BAR + (CELL_SIZE * 6);
    // printf("%d %d\n", x, y);
    MLV_draw_point(x, y, MLV_COLOR_RED);
    MLV_draw_rectangle(x, y, CELL_SIZE * numCol, CELL_SIZE * numRow, MLV_COLOR_BLACK);
    for (int i = 0; i < numRow - 1; i++) 
        MLV_draw_line(x, y + (i + 1) * CELL_SIZE, x + CELL_SIZE * numCol - 1, y + (i + 1) * CELL_SIZE, MLV_COLOR_BLACK);
    for (int i = 0; i < numCol - 1; i++) 
        MLV_draw_line(x + (i + 1) * CELL_SIZE, y, x + (i + 1) * CELL_SIZE, y + CELL_SIZE * numRow - 1, MLV_COLOR_BLACK);

    MLV_draw_rectangle(x - 50, y, 51, 160, MLV_COLOR_BLACK);
    MLV_draw_text(x - 30, y + 80, "LV1", MLV_COLOR_BLACK);
    MLV_draw_rectangle(x - 50, y + 160, 51, 160, MLV_COLOR_BLACK);
    MLV_draw_text(x - 30, y + 240, "LV2", MLV_COLOR_BLACK);
    MLV_draw_rectangle(x - 50, y + 320, 51, 160, MLV_COLOR_BLACK);
    MLV_draw_text(x - 30, y + 400, "LV3", MLV_COLOR_BLACK);
}

void displayGem(Gem gem) {
    MLV_draw_filled_circle(gem.center.x, gem.center.y, CELL_SIZE / 2, gem.color);
    MLV_draw_text(gem.center.x - 4, gem.center.y - 7, "%d", MLV_COLOR_BLACK, gem.level);
}

void displayListGem(ListGem list) {
    Node *node;
    Gem *gem;
    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 3; i++) {
            if (list.gemUnSet[j][i] != NULL) {
                gem = list.gemUnSet[j][i];
                displayGem(*gem);
            }
        }
    }
    for (node = list.gemSet.head; node != NULL; node = node->next) {
        gem = (Gem*)(node->data);
        displayGem(*gem);
    }
}

void displayTime(double time) {
    int x = 70;
    int y = 10;
    MLV_draw_text(x, y, "Time to next wave : %.2f", MLV_COLOR_BLACK, time);
}

void displayNumWave(int wave, int totalWave) {
    int x = 500;
    int y = 10;
    MLV_draw_text(x, y, "Wave : %d / %d", MLV_COLOR_BLACK, wave, totalWave);
}

void displayMessage(char *msg) {
    int x = 800;
    int y = 10;

    MLV_draw_text(x, y, "%s", MLV_COLOR_BLACK, msg);
}