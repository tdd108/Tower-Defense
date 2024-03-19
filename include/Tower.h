#ifndef TOWER_H
#define TOWER_H

#define MAX_TOWER 50
#define MAX_SEGMENT 4
#define TOWER_RANGE 140

#define d 10

#include "Segment.h"
#include "Position.h"
#include "Monster.h"
#include "Projectile.h"
#include "Gem.h"

typedef struct tower {
    int x; int y;
    Position center;
    int cost; int range;
    int numSegment; 
    int segment[MAX_SEGMENT]; // 4 directions, 
    Gem *gem;
    int aimed; Monster *target;
    int hasGem; 
    double coolDownTimer; int canAttack;
} Tower;

typedef struct listtower {
    int numTower;
    List towers;
} ListTowers;

Tower* newTower(int x, int y);

void addTower(ListTowers *list, Tower *tower);

void detectSegmentTower(Tower *tower, ListSegment list);

void aim(Tower *tower, ListSegment list);

void shoot(Tower *tower, ListProjectile *listProjectile);

int checkTower(Gem *gem, List towers);

float calculateDamage(int gemLevel, int gemHue, Monster monster);

int placeTower(Position pos, ListTowers *listTowers, ListSegment listSegment, Map *map, double *mana);

#endif
