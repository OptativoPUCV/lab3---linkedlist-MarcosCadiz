#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list = (List *)malloc(sizeof(List));
  assert(list != NULL);
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
  
}

void * firstList(List * list) {
  if (list == NULL || list->head == NULL){
    return NULL;
  }
  list->current = list->head;
  return list->current->data;
  
}

void * nextList(List * list) {
  if (list == NULL || list->head == NULL || list->current == NULL || list->current->next == NULL){
    return NULL;
  }
  list->current = list->current->next;
  return list->current->data;
  
}

void * lastList(List * list) {
  if (list == NULL || list->head == NULL){
    return NULL;
  }
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if (list == NULL || list->head == NULL || list->current == NULL || list->current->prev == NULL){
    return NULL;
  }
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  if (list == NULL){
    return;
  }
  Node * node = createNode(data);
  if (list->head == NULL){
    list->head = node;
    list->tail = node;
  }
  else{
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list == NULL){
    return;
  }
  Node * node = createNode(data);
  if (list->current == NULL){
    list->head = node;
    list->tail = node;
    
  }
  else{
    node->next = list->current->next;
    node->prev = list->current;
    if (list->current->next == NULL){
      list->tail = node; 
    }
    else{
      list->current->next->prev = node;
    }
    list->current->next = node;
  }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list == NULL || list->head == NULL || list->current == NULL){
    return NULL;
  }
  void * data = list->current->data;
  if (list->current->prev == NULL){
    list->head = list->current->next;
    if (list->current->next == NULL){
      list->tail = NULL;
    }
    else{
      list->current->next->prev = NULL;
    }
  }
  else{
    list->current->prev->next = list->current->next;
    if (list->current->next == NULL){
      list->tail = list->current->prev;
    }
    else{
      list->current->next->prev = list->current->prev;
    }
  }
  free(list->current);
  list->current = NULL;
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}