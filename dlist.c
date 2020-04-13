#include "dlist.h"
#include "utils.c"


typedef struct dnode dnode;
struct dnode {
  int data;
  dnode* next;
  dnode* prev;
};

dnode* dnode_create(int data, dnode* next, dnode* prev) {
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->next = next;
  p->prev = prev;

  return p;
}

typedef struct dlist dlist;
struct dlist {
  dnode* head;
  dnode* tail;
  size_t size;
};

dlist* dlist_create() {
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;

  return p;
}

int dlist_front(dlist* list){
  return list->head->data;
}

int dlist_back(dlist* list){
  return list->tail->data;
}
void dlist_clear(dlist* list){
  while(!dlist_empty(list)){dlist_popfront(list);}
}

void dlist_popfront(dlist* list) {
  if( list->head == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  dnode* p = list->head;
  list->head = list->head->next;
  if(list->size != 1) { list->head->prev = NULL; }
  free(p);
  --list->size;
}

void dlist_popback(dlist* list){
  if( list->tail == NULL ) { fprintf(stderr, "list is empty\n"); exit(1); }
  if (list->size == 1) { dlist_popfront(list); return; }
  dnode* p = list->tail;
  list->tail = p->prev;
  free(p);
  list->tail->next = NULL;
  --list->size;
}

void dlist_pushfront(dlist* list, int num) {
  dnode* p = dnode_create(num, list->head, NULL);
  if(list->size != 0) { list->head->prev = p; }
  list->head = p;
  if (list->size == 0) {
    list-> tail = p;
    list->tail->prev = NULL;
  }
  ++list->size;
}

void dlist_pushback(dlist* list, int num){
  if (list->size == 0) { dlist_pushfront(list, num); return; }
  dnode* p = dnode_create(num, NULL, list->tail);
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}

int dlist_empty(dlist* list) { return list->size == 0; }
size_t slist_size(slist* list){
  return list->size;
}


void dlist_print(dlist* list, const char* msg) {
  printf("%s\n", msg);
  if (dlist_empty(list)) { printf("List is empty\n"); return; }

  dnode* p = list->head;
  while (p != NULL) {
    printf("%p <-- %d (%p) --> %p\n", p->prev, p->data, p, p->next);
    p = p->next;
  }
}
