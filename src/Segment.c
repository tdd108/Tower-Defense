#include <stdio.h>
#include <stdlib.h>

#include "Segment.h"

void dividePathToSegment(Map map, ListSegment *list) {
    list->segments = (Segment*)malloc(map.numTurn  * sizeof(Segment));
    if (list->segments == NULL) {
        printf("malloc failed.\n");
        free(list->segments);
        list->segments = NULL;
        return;
    }

    list->numberSegment = 0;

    int segmentStartIndex = 0;
    int id = 0;

    for (int i = 0; i < map.pathlength; i++) {
        if (map.path[i].type == TURN || map.path[i].type == CAMP) {
            list->segments[list->numberSegment].idSegment = id;
            list->segments[list->numberSegment].startIndex = segmentStartIndex;
            list->segments[list->numberSegment].start = map.path[segmentStartIndex];
            list->segments[list->numberSegment].endIndex = i;
            list->segments[list->numberSegment].end = map.path[i];
            list->segments[list->numberSegment].monsters = newList();
            list->segments[list->numberSegment].numMonsters = 0;
            segmentStartIndex = i + 1;
            list->numberSegment++;
            id++;
        }
    }
}

void deleteMonsterFromSegment(Segment *segment, int idMonster) {
    Node *current = segment->monsters.head;
    Node *prev = NULL;

    if (current != NULL && ((Monster*)(current->data))->idMonster == idMonster) {
        segment->monsters.head = current->next;
        segment->numMonsters--;
        free(current);
        return;
    }

    while (current != NULL && ((Monster*)(current->data))->idMonster != idMonster) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    prev->next = current->next;
    segment->numMonsters--;
    free(current);
}

void addMonsterToSegment(Segment *segment, Monster *monster) {
    insertNode(&(segment->monsters), monster);
    segment->numMonsters++;
}

void toNextSegment(Monster *monster, ListSegment *list, Map map) {
    if (monster->currentSegment == -1) {
        monster->currentSegment++;
        addMonsterToSegment(&(list->segments[monster->currentSegment]), monster);
    }
    else if (monster->currentPosition == list->segments[monster->currentSegment].endIndex &&
        monster->currentSegment == list->segments[monster->currentSegment].idSegment && monster->currentPosition < map.pathlength - 1) {
        deleteMonsterFromSegment(&(list->segments[monster->currentSegment]), monster->idMonster);
        addMonsterToSegment(&(list->segments[monster->currentSegment + 1]), monster);
        monster->currentSegment++;
    }
}