#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MLV/MLV_all.h>

#include "Monster.h"

Monster *newMonster(int idMonster, float speed, float hp, MLV_Color color, Cell startCell) {
    Monster *newMonster = (Monster*)malloc(sizeof(Monster));
    newMonster->idMonster = idMonster;
    newMonster->x = startCell.center.x;
    newMonster->y = startCell.center.y;
    newMonster->currentPosition = 0;
    newMonster->targetPosition = 1;
    newMonster->speed = speed;
    newMonster->hp = hp;
    newMonster->initialHP = hp;
    newMonster->effect = EFF_NONE;
    newMonster->color = color;
    newMonster->currentSegment = -1;
    newMonster->projectile = 0;
    newMonster->hue = getRandomNumber(0, 360);
    newMonster->color = hueToRgb(newMonster->hue);

    return newMonster;
}

int determineWaveType(int numWave) {
    int type, randomValue;
    do {
        randomValue = getRandomNumber(0, 100);
        if (randomValue < 50)
            type = NORMAL;
        else if (randomValue < 70)
            type = CROWD;
        else if (randomValue < 90)
            type = AGILE;
        else
            type = BOSS;
    } while (type == BOSS && numWave < 4);

    return type;
}

void generateWaves(Wave **waves, int numWaves, Cell startCell) {
    if (*waves != NULL) 
        free(*waves);

    *waves = (Wave*)malloc(numWaves * sizeof(Wave));

    if (*waves == NULL) {
        printf("malloc of waves failed.\n");
        return;
    }

    float speed;
    float hp;
    int id = 0;

    for (int idWave = 0; idWave < numWaves; idWave++) {
        (*waves)[idWave].type = determineWaveType(idWave);
        switch ((*waves)[idWave].type) {
            case NORMAL:
                (*waves)[idWave].numMonsters = NORMAL_AMOUNT;
                speed = NORMAL_SPEED;
                break;
            
            case CROWD:
                (*waves)[idWave].numMonsters = CROWD_AMOUNT;
                speed = CROWD_SPEED;
                break;
            
            case AGILE:
                (*waves)[idWave].numMonsters = AGILE_AMOUNT;
                speed = AGILE_SPEED;
                break;
            
            case BOSS:
                (*waves)[idWave].numMonsters = BOSS_AMOUNT;
                speed = BOSS_SPEED;
                break;
            
            default:
                break;
                
        }
        hp = H * pow(1.2, (double)idWave);
        (*waves)[idWave].monsters = newList();
        for (int idMonster = 0; idMonster < (*waves)[idWave].numMonsters; idMonster++) {
            insertNode(&((*waves)[idWave].monsters), newMonster(id, speed, hp, MLV_COLOR_BLACK, startCell));
            id++;
        }
    }
}

void deleteMonster(Wave *wave, int idMonster) {
    Node *current = wave->monsters.head;
    Node *prev = NULL;

    if (current != NULL && ((Monster*)(current->data))->idMonster == idMonster) {
        wave->monsters.head = current->next;
        wave->numMonsters--;
        free(current->data);
        free(current);
        return;
    }

    while (current != NULL && ((Monster*)(current->data))->idMonster != idMonster) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    wave->numMonsters--;
    free(current->data);
    free(current);
}

void moveMonster(Monster *monster, Map map) {
    if (monster == NULL)
        return;

    float slowFactor = 1;
    if (monster->effect == EFF_SLOW)
        slowFactor = 1.5;
    else if (monster->effect == EFF_VAPOR)
        slowFactor = 1.25;

    float destX = (float)map.path[monster->targetPosition].center.x;
    float destY = (float)map.path[monster->targetPosition].center.y;
    float dx = destX - monster->x;
    float dy = destY - monster->y;

    // Calculate the movement direction
    float length = sqrt(dx * dx + dy * dy); // Calculate the distance

    if (length > monster->speed) {
        float factor = monster->speed / length; // Calculate the movement factor
        factor /= slowFactor;
        monster->x += dx * factor; // Update position based on speed and direction
        monster->y += dy * factor;
        monster->center.x = monster->x;
        monster->center.y = monster->y;
    }
    else if (monster->targetPosition < map.pathlength - 1) {
        monster->currentPosition = monster->targetPosition;
        monster->targetPosition++;
    }
    else {
        monster->currentPosition = monster->targetPosition;
    }
}

void monsterEffectController(Monster *monster, double time) {
    if (monster->effect == EFF_SPLASH) {
        if (monster->timerEffect <= 0) {
            monster->effect = EFF_NONE;
            return;
        }
        else {
            monster->timerEffect -= time;
            return;
        }
    }
    if (monster->effect == EFF_SLOW) {
        if (monster->timerEffect <= 0) {
            monster->effect = EFF_NONE;
            return;
        }
        else {
            monster->timerEffect -= time;
            return;
        }
    }
    if (monster->effect == EFF_POISON) {
        if (monster->timerEffect <= 0) {
            monster->effect = EFF_NONE;
            return;
        }
        else {
            monster->timerEffect -= time;
            monster->timerPoison += time;
            if (monster->timerPoison >= 0.5) {
                monster->hp -= monster->damagePoison;
                monster->timerPoison = 0;
            }
            return;
        }
    }
    if (monster->effect == EFF_VAPOR) {
        if (monster->timerEffect <= 0) {
            monster->effect = EFF_NONE;
            return;
        }
        else {
            monster->timerEffect -= time;
            return;
        }
    }
}