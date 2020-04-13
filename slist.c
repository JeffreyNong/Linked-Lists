#include "slist.h"
#include "utils.c"

typedef struct snode snode;
struct snode {
  int data;
  snode* next;
};

snode* snode_create(int data, snode* next) {
  snode* p = (snode*)malloc(sizeof(snode));
  p->data = data;
  p->next = next;

  return p;
}

typedef struct slist slist;
struct slist {
  snode* head;
  snode* tail;
  size_t size;
};

slist* slist_create() {
  slist* p = (slist*)malloc(sizeof(slist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;

  return p;
}
int slist_empty(slist* list){
  return list->size == 0;
}
size_t slist_size(slist* list){
  return list->size;
}

void slist_pushfront(slist* list, int num) {
  snode* p = snode_create(num, list->head);
  list->head = p;
  if (list->size == 0) { list-> tail = p; }
  ++list->size;
}

void slist_pushback(slist* list, int num){
  if (list->size == 0) { slist_pushfront(list, num); return; }
  snode* p = snode_create(num, NULL);
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}
void slist_popfront(slist* list) {
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  snode* p = list->head;
  list->head = list->head->next;
  free(p);
  --list->size;
}

void slist_popback(slist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  if (list->size == 1) { slist_popfront(list); return; }

  snode* p = list->head;
  snode* prev = p;
  while(p->next != NULL) {
  prev = p;
  p = p->next;
}
  prev->next = NULL;
  free(p);
  list->tail = prev;
  --list->size;
}
int slist_front(slist* list){
  return list->head->num;
}
int slist_back(slist* list){
  return list->tail->num;
}
void slist_clear(slist* list){
  while(!slist_empty(list)){slist_popfront(list);
  }
}
void slists_print(slist* list, const char* msg){
  printf("%s\n", msg);
  snode* p = list->head;
  while(p != NULL){
    printf("%d --> %p\n", p->data, p->next);
    p = p-> next;
  }
}
