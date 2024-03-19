#ifndef MONSTER_H
#define MONSTER_H

#define H 50 //change if needed
#define MONSTER_SIZE 7
#define NORMAL_PROB 50
#define CROWD_PROB 70
#define AGILE_PROB 90

#define NORMAL_SPEED 0.5
#define CROWD_SPEED 0.5
#define AGILE_SPEED 1.3
#define BOSS_SPEED 0.5

#define NORMAL_AMOUNT 12
#define CROWD_AMOUNT 24
#define AGILE_AMOUNT 12
#define BOSS_AMOUNT 2

#define SPLASH_TIMER 10

#include "Map.h"
#include "LinkedList.h"
#include "utils.h"

typedef enum {
    EFF_SPLASH,
    EFF_POISON,
    EFF_SLOW,
    EFF_VAPOR,
    EFF_NONE,
} Effect;

typedef enum {
    NORMAL,
    CROWD,
    AGILE,
    BOSS
} WaveType;

typedef struct monster {
    int idMonster;
    float x; float y; Position center;
    float speed;
    float hp; float initialHP;
    Effect effect;
    double timerEffect;
    double timerPoison;
    float damagePoison;
    int currentPosition; int targetPosition; int currentSegment;
    int hue;
    int round;
    MLV_Color color;
    int projectile;
} Monster;

typedef struct wave {
    WaveType type;
    int numMonsters;
    List monsters;
} Wave;

int determineWaveType(int numWave);

Monster *newMonster(int idMonster, float speed, float hp, MLV_Color color, Cell startCell);

//Function to initialize 1 wave
void initializeWave(Wave *wave, WaveType type);

//Function to choose randomly type of waves
void generateWaves(Wave **waves, int numWaves, Cell startCell);

void deleteMonster(Wave *wave, int idMonster);

void moveMonster(Monster *monster, Map map);

void monsterEffectController(Monster *monster, double time);

void moveWave(Wave *wave, Map map);

#endif