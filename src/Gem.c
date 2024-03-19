#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "Gem.h"

Gem *newGem(GemType type, int level, int hue, PureGemElement element) {
    Gem *newGem = (Gem*)malloc(sizeof(Gem));
    newGem->type = type;
    newGem->level = level;
    newGem->color = hueToRgb(hue);
    newGem->element = element;
    return newGem;
}

PureGemElement getGemElement() {
    int element = getRandomNumber(0, 2);
    
    if (element == PYRO)
        return PYRO;
    
    if (element == DENDRO)
        return DENDRO;
    
    if (element == HYDRO)
        return HYDRO;
    
    return NO_ELEMENT;
}

int combineGem(Gem *gem1, Gem *gem2) {
    if (gem1 == gem2)
        return 0;

    if (gem1->level != gem2->level)
        return 0;
    
    int newHue, newLevel;
    GemType newType;
    PureGemElement newElement;

    if (gem1->type != gem2->type)
        newType = MIXED;
    else
        newType = gem1->type;

    newHue = (gem1->hue + gem2->hue) / 2;
    if (newHue >= 360)
        newHue %= 360;

    if (gem1->element != gem2->element)
        newElement = NO_ELEMENT;
    else
        newElement = gem1->element;

    newLevel = gem1->level + gem2->level;

    // gem = newGem(newType, newLevel, newHue, newElement);
    gem2->type = newType;
    gem2->hue = newHue;
    gem2->level = newLevel;
    gem2->element = newElement;
    gem2->color = hueToRgb(newHue);

    return 1;
}

int getGemHue(PureGemElement element) {
    int hue;

    if (element == PYRO) {
        hue = getRandomNumber(-30, 30);
        if (hue < 0)
            hue = 360 + hue;
        return hue;
    }

    if (element == DENDRO) {
        hue = getRandomNumber(90, 150);
        return hue;
    }

    if (element == HYDRO) {
        hue = getRandomNumber(210, 270);
        return hue;
    }

    return 0;
}

void addNewPureGem(ListGem *list, int level) {
    if (list->numGemUnSet >= MAX_UNSET_GEM)
        return;
        
    PureGemElement element = getGemElement();
    int hue = getGemHue(element);
    Gem *gem = newGem(PURE, level, hue, element);
    int x = 0, y = 0;
    int getXY = 0;
    int offSetX = 1250;
    int offSetY = 310;
    //finding where to put the new gem
    for (y = 0; y < MAX_GEM_GRID_ROW; y++) {
        for (x = 0; x < MAX_GEM_GRID_COL; x++) {
            if (list->gemUnSet[y][x] == NULL) {
                getXY = 1;
                break;
            }
        }
        if (getXY)
            break;
    }

    list->gemUnSet[y][x] = gem;
    x = x * CELL_SIZE + offSetX;
    y = y * CELL_SIZE + offSetY;
    gem->x = x;
    gem->y = y;
    gem->center.x = x;
    gem->center.y = y;
    list->numGemUnSet++;
}

void addGemSet(ListGem *list, Gem *gem) {
    insertNode(&(list->gemSet), gem);
    list->numGemSet++;
}

void deleteGemUnSet(ListGem *list, Gem *gem) {
    for (int y = 0; y < MAX_GEM_GRID_ROW; y++) {
        for (int x = 0; x < MAX_GEM_GRID_COL; x++) {
            if (list->gemUnSet[y][x] == gem) {
                list->gemUnSet[y][x] = NULL;
                list->numGemUnSet--;
                return;
            }
        }
    }
}

Gem *checkDistanceGem(ListGem list, Gem *gem) {
    for (int y = 0; y < MAX_GEM_GRID_ROW; y++) {
        for (int x = 0; x < MAX_GEM_GRID_COL; x++) {
            if (list.gemUnSet[y][x] != NULL && 
                distance(list.gemUnSet[y][x]->center, gem->center) < CELL_SIZE / 2) {
                return list.gemUnSet[y][x];
            }
        }
    }
    return NULL;
}