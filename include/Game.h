#ifndef GAME_H
#define GAME_H

#include "Display.h"
#include "Segment.h"
#include "Input.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define TIME_TO_NEXT_WAVE 35

void gameInput(MLV_Event event);

void wavesController(Wave *waves, int numWave, Map map, ListSegment *listSegment, double time, double *mana, double manaMax, int level);

void towersController(ListTowers *listTower, ListSegment listSegment, double time, ListProjectile *listProjectile);

void projectilesController(ListProjectile *list, ListSegment listSeg);

void effectController(Projectile proj, ListSegment listSeg);

void pyroEffect(ListSegment listSeg, Monster target, Projectile proj);

void hydroEffect(Projectile proj);

void dendroEffect(Projectile proj);

void vaporization(ListSegment listSeg, Monster target, Projectile proj);

#endif