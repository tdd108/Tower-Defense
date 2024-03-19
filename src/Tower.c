#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Tower.h"

Tower* newTower(int x, int y) {
    Tower *newTower = (Tower*)malloc(sizeof(Tower));
    newTower->x = x;
    newTower->y = y;
    newTower->center = centerPosition(x, y);
    newTower->center.x += 70; //offset_map_x
    newTower->center.y += 50; //offset_map_y
    newTower->numSegment = 0;
    newTower->range = TOWER_RANGE;
    newTower->aimed = 0;
    newTower->target = NULL;
    newTower->canAttack = 1;
    newTower->coolDownTimer = 2;
    newTower->gem = NULL;
    return newTower;
}

void addTower(ListTowers *list, Tower *tower) {
    insertNode(&(list->towers), tower);
    list->numTower++;
}

void detectSegmentTower(Tower *tower, ListSegment list) {
    Cell start, end;
    // for all the segments check which segment is in range of the tower.
    for (int i = 0; i < list.numberSegment; i++) {
        start = list.segments[i].start;
        end = list.segments[i].end;
        if (distance(tower->center, start.center) < tower->range ||
            distance(tower->center, end.center) < tower->range) {
            tower->segment[tower->numSegment] = i;
            tower->numSegment++;
        }
        else if (start.y == end.y) {
            if (((start.x <= tower->x && tower->x <= end.x) ||
                (end.x < tower->x && tower->x <= start.x)) &&
                abs(tower->center.y - start.center.y) < tower->range) {
                tower->segment[tower->numSegment] = i;
                tower->numSegment++;
            }    
        } else if (start.x == end.x) {
            if (((start.y <= tower->y && tower->y <= end.y) ||
                (end.y < tower->y && tower->y <= start.y)) &&
                abs(tower->center.x - start.center.x) < tower->range) {
                tower->segment[tower->numSegment] = i;
                tower->numSegment++;
            }
        }
    }
}

void aim(Tower *tower, ListSegment list) {
    float lastDistance, newDistance;
    tower->target = NULL;
    for (int idSeg = 0; idSeg < tower->numSegment; idSeg++) {
        Segment segment = list.segments[tower->segment[idSeg]];
        Monster *monster;
        Node *node = segment.monsters.head;
        for (node = segment.monsters.head; node != NULL; node = node->next) {
            monster = (Monster*)(node->data);
            if (monster->currentPosition < 2)
                continue;
            newDistance = distance(tower->center, monster->center);
            if (tower->target != NULL) {
                lastDistance = distance(tower->center, tower->target->center);
                if (newDistance > lastDistance)
                    continue;
                if (monster->hp < tower->target->hp)
                    continue;
            }
            if (newDistance < tower->range) {
                tower->target = monster;
            }
        }
    }
}

float calculateDamage(int gemLevel, int gemHue, Monster monster) {
    float damage;
    damage = d * pow((double)2, (double)gemLevel) * (1 - (cos((double)gemHue - (double)monster.hue) / 2));
    return damage;
}

void shoot(Tower *tower, ListProjectile *listProjectile) {
    if (tower->target == NULL)
        return;

    Projectile *proj = newProjectile(tower->center.x, tower->center.y, tower->target, 
                                    tower->gem->level, tower->gem->hue, tower->gem->element);
    proj->damage = calculateDamage(tower->gem->level, tower->gem->hue, *(tower->target));
    addProjectile(listProjectile, proj);
    tower->coolDownTimer = 0.7;
}

int checkTower(Gem *gem, List towers) {
    Node *node;
    Tower *tower;
    for (node = towers.head; node != NULL; node = node->next) {
        tower = (Tower*)(node->data);
        if (tower->gem != NULL)
            continue;
        if (distance(gem->center, tower->center) < CELL_SIZE) {
            tower->gem = gem;
            gem->center = tower->center;
            return 1;
        }
    }
    return 0;
}

int placeTower(Position pos, ListTowers *listTowers, ListSegment listSegment, Map *map, double *mana) {
    Tower *tower; 
    int x, y;
    x = pos.x;
    y = pos.y;
    if (map->grid[y][x].type != EMPTY)
        return 2;
    double costTower = 100 * pow(2, listTowers->numTower + 1 - 4);
    if (listTowers->numTower >= 3 && *mana > costTower)
        *mana -= costTower;
    else if (*mana < costTower)
        return 1;
    map->grid[y][x].type = TOWER;
    tower = newTower(x, y);
    detectSegmentTower(tower, listSegment);
    addTower(listTowers, tower);
    return 0;
}