#ifndef PROJECTILE_H
#define PROJECTILE_H

#define MAX_PROJECTILE 100

#include "Position.h"
#include "Monster.h"

typedef enum {
    PROJ_PYRO,
    PROJ_DENDRO,
    PROJ_HYDRO,
    PROJ_NO_ELEMENT,
} ProjectileElement;

typedef struct projectile {
    int id;
    float x; float y;
    Position center;
    int speed;
    int level;
    int hue;
    ProjectileElement element;
    MLV_Color color;
    float damage;
    Monster *target;
} Projectile;

typedef struct listprojectile {
    int numProjectile;
    List projectiles;
} ListProjectile;

Projectile *newProjectile(float x, float y, Monster *target, int level, int hue, ProjectileElement element);

void moveProjectile(Projectile *projectile);

int meetTarget(Projectile projectile);

void addProjectile(ListProjectile *listProjectile, Projectile *newProjectile);

void deleteProjectile(ListProjectile *list, Projectile *projectile);

#endif