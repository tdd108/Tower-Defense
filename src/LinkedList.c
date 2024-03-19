#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

Node *newNode(void *data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

List newList() {
    List newList;
    newList.head = NULL;
    newList.numberNode = 0;
    return newList;
}
 
void insertNode(List *list, void *data) {
    Node *node = newNode(data);
    node->next = list->head;
    list->head = node;
    list->numberNode++;
}

void freeList(List *list) {
    Node *tmp;
    while (list->head != NULL) {
        tmp = list->head;
        list->head = list->head->next;
        if (tmp->data != NULL) {
            free(tmp->data);
            tmp->data = NULL;
        }
        if (tmp != NULL) {
            free(tmp);
            tmp = NULL;
        }
    } 
}