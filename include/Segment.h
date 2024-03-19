#ifndef SEGMENT_H
#define SEGMENT_H

#include "Map.h"
#include "Monster.h"

#define MAX_SEGMENT_LENGTH 5
#define MAX_MONSTER_PER_SEGMENT 50

// Structure representing a linear segment
typedef struct segment {
    int idSegment;
    int startIndex; int endIndex;
    Cell start; Cell end;
    int numMonsters;
    List monsters;
} Segment;

// structure representing a list of segments
typedef struct listSegment {
    int numberSegment;
    Segment *segments;
} ListSegment;

void dividePathToSegment(Map map, ListSegment *segment);

void deleteMonsterFromSegment(Segment *segment, int idMonster);

void addMonsterToSegment(Segment *segment, Monster *monster);

void toNextSegment(Monster *monster, ListSegment *list, Map map);

#endif