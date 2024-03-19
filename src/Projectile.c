#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Projectile.h"

Projectile *newProjectile(float x, float y, Monster *target, int level, int hue, ProjectileElement element) {
    Projectile *newProjectile = (Projectile*)malloc(sizeof(Projectile));
    newProjectile->x = x;
    newProjectile->y = y;
    newProjectile->center = centerPosition(x, y);
    newProjectile->speed = 3;
    newProjectile->target = target;
    newProjectile->level = level;
    newProjectile->element = element;
    newProjectile->hue = hue;
    newProjectile->color = hueToRgb(hue);
    target->projectile++;
    return newProjectile;
}

void moveProjectile(Projectile *projectile) {
    if (projectile->target == NULL)
        return;

    Monster *target = projectile->target;

    float dx = target->x - projectile->x;
    float dy = target->y - projectile->y;

    // Calculate the movement direction
    float length = sqrt(dx * dx + dy * dy); // Calculate the distance

    if (length > projectile->speed) {
        float factor = projectile->speed / length; // Calculate the movement factor
        projectile->x += dx * factor; // Update position based on speed and direction
        projectile->y += dy * factor;
        projectile->center.x = projectile->x;
        projectile->center.y = projectile->y;
    }
}

int meetTarget(Projectile projectile) {
    if (distance(projectile.center, projectile.target->center) <= MONSTER_SIZE) {
        return 1;
    }
    return 0;
}

void deleteProjectile(ListProjectile *list, Projectile *projectile) {
    Node *current = list->projectiles.head;
    Node *prev = NULL;

    if (current != NULL && ((Projectile*)(current->data)) == projectile) {
        list->projectiles.head = current->next;
        list->numProjectile--;
        free(current->data);
        free(current);
        return;
    }

    while (current != NULL && ((Projectile*)(current->data)) != projectile) {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    prev->next = current->next;
    list->numProjectile--;
    free(current->data);
    free(current);
}

void addProjectile(ListProjectile *listProjectile, Projectile *newProjectile) {
    insertNode(&(listProjectile->projectiles), newProjectile);
    listProjectile->numProjectile++;
}