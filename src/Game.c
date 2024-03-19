#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "Game.h"

void wavesController(Wave *waves, int numWave, Map map, ListSegment *listSegment, double time, double *mana, double manaMax, int level) {
    Node *node;
    Node *next = NULL;
    Monster *monster;

    for (int i = 0; i < numWave; i++) {
        if (waves[i].numMonsters <= 0)
            continue;

        node = waves[i].monsters.head;
        while (node != NULL) {
            monster = (Monster*)(node->data);
            if (monster->hp <= 0) {
                next = node->next;
                *mana += MIN(monster->initialHP * pow(1.3, level) * 10 / 100, manaMax - *mana);
                deleteMonsterFromSegment(&listSegment->segments[monster->currentSegment], ((Monster*)(node->data))->idMonster);

                if (monster->projectile == 0) {
                    deleteMonster(&waves[i], ((Monster*)(node->data))->idMonster);
                }

                node = next;
            } 
            else if (monster->currentPosition == map.pathlength - 1) {
                *mana -= (0.15) * monster->initialHP * pow(1.3, level);
                deleteMonsterFromSegment(&listSegment->segments[monster->currentSegment], ((Monster*)(node->data))->idMonster);
                monster->x = map.monsterNest.center.x;
                monster->y = map.monsterNest.center.y;
                monster->currentPosition = 0;
                monster->targetPosition = 1;
                monster->currentSegment = -1;
                monster->round = 1;
            }
            else {
                monsterEffectController(monster, time);
                moveMonster(monster, map);
                toNextSegment(monster, listSegment, map);

                if (monster->round != 1 && monster->currentPosition < 1)
                    break;

                node = node->next;
            }
        }
    }
}

void towersController(ListTowers *listTower, ListSegment listSegment, double time, ListProjectile *listProjectile) {
    Node *node;
    Tower *tower;

    for (node = listTower->towers.head; node != NULL; node = node->next) {
        tower = (Tower*)(node->data);
        if (tower->gem == NULL)
            continue;

        aim(tower, listSegment);
        
        tower->coolDownTimer -= time;

        if (tower->coolDownTimer <= 0)
            shoot(tower, listProjectile);
    }
}

void projectilesController(ListProjectile *list, ListSegment listSeg) {
    Node *node = list->projectiles.head;
    Node *next = NULL;
    Projectile *projectile;

    while (node != NULL) {
        projectile = (Projectile*)(node->data);

        if (meetTarget(*projectile)) {
            next = node->next;
            effectController(*projectile, listSeg);
            projectile->target->hp -= projectile->damage;
            projectile->target->effect = projectile->element;
            projectile->target->projectile--;
            deleteProjectile(list, projectile);
            node = next;
        }
        else {
            moveProjectile(projectile);
            node = node->next;
        }

    }
}

void effectController(Projectile proj, ListSegment listSeg) {
    if (proj.element == PROJ_PYRO)
        pyroEffect(listSeg, *proj.target, proj);
    else if (proj.element == PROJ_HYDRO)
        hydroEffect(proj);
    else if (proj.element == PROJ_DENDRO)
        dendroEffect(proj);
}

void pyroEffect(ListSegment listSeg, Monster target, Projectile proj) {
    Segment currentSeg = listSeg.segments[target.currentSegment];
    proj.target->timerEffect = 3;
    Node *node = currentSeg.monsters.head;
    Monster *monster;
    float damage;

    while (node != NULL) {
        monster = (Monster*)(node->data);

        if (abs(monster->currentPosition - target.currentPosition) <= 2) {
            damage = calculateDamage(proj.level, proj.hue, *monster);
            monster->hp -= 0.15 * damage;
            monster->effect = EFF_SPLASH;
            monster->timerEffect = 3;
        }

        node = node->next;
    }
}

void hydroEffect(Projectile proj) {
    proj.target->effect = EFF_SLOW;
    proj.target->timerEffect = 10;
}

void dendroEffect(Projectile proj) {
    proj.target->effect = EFF_POISON;
    proj.target->timerEffect = 10;
    proj.target->damagePoison = (2.5 / 100) * proj.damage;
}

void vaporization(ListSegment listSeg, Monster target, Projectile proj) {
    Segment currentSeg = listSeg.segments[target.currentSegment];
    proj.target->timerEffect = 3;
    Node *node = currentSeg.monsters.head;
    Monster *monster;
    float damage;

    while (node != NULL) {
        monster = (Monster*)(node->data);

        if (abs(monster->currentPosition - target.currentPosition) <= 3) {
            damage = calculateDamage(proj.level, proj.hue, *monster) * (5 / 100);
            monster->hp -= damage;
            monster->effect = EFF_VAPOR;
            monster->timerEffect = 5;
        }

        node = node->next;
    }
}
