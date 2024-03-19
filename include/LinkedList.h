#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
    void *data;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    int numberNode;
} List;

Node *newNode(void *data);

List newList();

void insertNode(List *list, void *data);

void freeList(List *list);

#endif