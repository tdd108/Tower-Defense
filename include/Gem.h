#ifndef GEM_H
#define GEM_H

#include "Position.h"
#include "LinkedList.h"
#include "utils.h"

#define MAX_UNSET_GEM 36

#define PYRO_RANGE_1_MIN 0
#define PYRO_RANGE_1_MAX 30
#define PYRO_RANGE_2_MIN 330
#define PYRO_RANGE_2_MAX 359
#define DENDRO_RANGE_1_MAX 90
#define DENDRO_RANGE_1_MIN 150
#define HYDRO_RANGE_1_MIN 210
#define HYDRO_RANGE_1_MAX 270

#define MAX_GEM_GRID_COL 3
#define MAX_GEM_GRID_ROW 12

typedef enum {
    PURE,
    MIXED
} GemType;

typedef enum {
    PYRO,
    DENDRO,
    HYDRO,
    NO_ELEMENT,
} PureGemElement;

typedef struct gem {
    float x; float y;
    Position center;
    int idGem;
    GemType type;
    PureGemElement element;
    int level;
    int hue;
    MLV_Color color;
} Gem;

typedef struct listgem {
    int numGemSet;
    int numGemUnSet;
    List gemSet;
    Gem *gemUnSet[MAX_GEM_GRID_ROW][MAX_GEM_GRID_COL];
} ListGem;

Gem *newGem(GemType type, int level, int hue, PureGemElement element);

PureGemElement getGemElement();

int getGemHue(PureGemElement element);

void addNewPureGem(ListGem *list, int level);

void addGemSet(ListGem *list, Gem *gem);

void deleteGemUnSet(ListGem *list, Gem *gem);

int combineGem(Gem *gem1, Gem *gem2);

Gem *checkDistanceGem(ListGem list, Gem *gem);

#endif