#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Game.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    int numberWave = 5;
    if (argc < 2) {
        printf("You can specify the number of waves desired.\nIf no number is specified, the default value is 5\n");
        printf("Usage: %s <integer>\n", argv[0]);
    }
    else {
        numberWave = atoi(argv[1]);
    }
    
    
    int numWave = 1;
    int frame = 0;
    double waveTimer = 0;
    double inGameTime = 0;
    int start = 0;
    int win = 0;
    char notice[1024] = "";
    int totalMonster = 0;

    double mana = 150;
    int level = 0;
    double manaMax = 2000 * pow(1.4, level);

    Map map;

    Wave *waves = NULL;

    ListSegment listSegment;

    ListTowers listTowers;
    listTowers.towers = newList();
    listTowers.numTower = 0;

    ListProjectile listProjectile;
    listProjectile.projectiles = newList();
    listProjectile.numProjectile = 0;

    MouseCursor cursor = newCursor();

    ListGem listGem;
    listGem.gemSet = newList();
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 3; x++) {
            listGem.gemUnSet[y][x] = NULL;
        }
    }
    listGem.numGemSet = 0;
    listGem.numGemUnSet = 0;

    startWindow();

    generateMap(&map);
    generateWaves(&waves, numberWave, map.monsterNest);
    dividePathToSegment(map, &listSegment);

    addNewPureGem(&listGem, 1);
    addNewPureGem(&listGem, 1);
    addNewPureGem(&listGem, 1);

    struct timespec end_time, new_time;

    while (1) {
        clock_gettime(CLOCK_REALTIME, &end_time);   

        MLV_actualise_window();

        // INPUT
        inputHandler(&cursor);

        if (mana <= 0)
            break;
        totalMonster = 0;
        for (int i = 0; i < numberWave; i++) {
            totalMonster += waves[i].numMonsters;
        }
        if (totalMonster == 0) {
            win = 1;
            break;
        }

        if (cursor.state == PLACE_TOWER) {
            int res = placeTower(cursor.pos, &listTowers, listSegment, &map, &mana);
            if (res == 2)
                strcpy(notice, "Cell is not emtpy");
            else if (res == 1)
                strcpy(notice, "Not enough mana");
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        }
        else if (cursor.state == ADD_GEM) {
            if (mana >= 100 * pow(2, cursor.level)) {
                addNewPureGem(&listGem, cursor.level);
                mana -= 100 * pow(2, cursor.level);
            } else {
                strcpy(notice, "Not enough mana");
            }
        }
        else if (cursor.state == DRAG_GEM) {
            getGemCursor(&cursor, listGem.gemUnSet);
        }
        else if (cursor.state == CHECK_TOWER) {
            if (!checkTower(cursor.gem, listTowers.towers)) {
                cursor.gem->center = cursor.gemLastPos;
            } else {
                deleteGemUnSet(&listGem, cursor.gem);
                addGemSet(&listGem, cursor.gem);
            }
            cursor.gem = NULL;
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        }
        else if (cursor.state == CHECK_GEM) {
            Gem *gem2, *gem1;
            gem1 = cursor.gem;
            gem2 = checkDistanceGem(listGem, gem1);
            int res = combineGem(gem1, gem2);
            if (gem2 != NULL && res && mana >= 100) {
                deleteGemUnSet(&listGem, gem1);
                mana -= 100;
            } else if (mana < 100) {
                strcpy(notice, "Not enough mana");
            } else {
                strcpy(notice, "Invalid gem");
            }
            cursor.gem->center = cursor.gemLastPos;
            cursor.gem = NULL;
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        }
        else if (cursor.option == OPTION_4) {
            if (mana >= 500 * pow(1.4, level)) {
                level += 1;
                manaMax = 2000 * pow(1.4, level);
                mana -= 500 * pow(1.4, level);
            } else {
                strcpy(notice, "Not enough mana");
            }
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        }
        else if (cursor.option == OPTION_1) {
            if (start && numWave != numberWave) {
                mana += (float) ((TIME_TO_NEXT_WAVE - waveTimer) / 100) * manaMax;
                waveTimer = TIME_TO_NEXT_WAVE;
            }
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        } 
        else if (cursor.option == OPTION_2) {
            start = 1;
            cursor.state = NONE;
            cursor.option = OPTION_NONE;
        }

        if (mana > manaMax)
            mana = manaMax;

        // CONTROLLER
        if (start)
            wavesController(waves, numWave, map, &listSegment, inGameTime, &mana, manaMax, level);
        towersController(&listTowers, listSegment, inGameTime, &listProjectile);
        projectilesController(&listProjectile, listSegment);

        //RENDERER
        displayFillScreen();
        displayGemGrid(cursor.state);
        displayGridOption();
        displayMap(map);
        displayWaves(numWave, waves);
        displayListTower(listTowers);
        displayListProjectile(listProjectile);
        displayListGem(listGem);
        displayManaBar(mana, manaMax);
        displayTime(TIME_TO_NEXT_WAVE - waveTimer);
        displayNumWave(numWave, numberWave);
        displayMessage(notice);
        strcpy(notice, "");
        frame++;

        if (waveTimer > TIME_TO_NEXT_WAVE && numWave < numberWave) {
            numWave++;
            waveTimer = 0;
        } 
        else if (numWave == numberWave) {
            waveTimer = 0;
        }

        clock_gettime(CLOCK_REALTIME, &new_time);
        double frametime = new_time.tv_sec - end_time.tv_sec;
        frametime += (new_time.tv_nsec - end_time.tv_nsec) / 1.0E9;
        double extra_time = 1.0 / 60 - frametime;
        if (start != 0)
            waveTimer += frametime + extra_time;
        inGameTime = frametime + extra_time;
        if (extra_time > 0) {
            MLV_wait_milliseconds((int)(extra_time * 1000));
        }
    }

    if (!win) {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_text(200, 200, "GAME OVER", MLV_COLOR_RED, 10000);
        MLV_update_window();
        MLV_wait_keyboard(NULL, NULL, NULL);
    }
    else {
        MLV_clear_window(MLV_COLOR_BLUE1);
        MLV_draw_text(200, 200, "YOU WIN", MLV_COLOR_RED, 10000);
        MLV_update_window();
        MLV_wait_keyboard(NULL, NULL, NULL);
    }
    
    free(map.path);
    for (int i = 0; i < numberWave; i++)
        freeList(&waves[i].monsters);
    free(waves);
    for (int i = 0; i < listSegment.numberSegment; i++) {
        if (listSegment.segments[i].numMonsters > 0)
            freeList(&(listSegment.segments[i].monsters));
    }
    free(listSegment.segments);
    freeList(&listTowers.towers);
    freeList(&listGem.gemSet);
    endWindow();
    return 0;
}