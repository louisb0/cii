#include "../include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack_T {
  int len;

  struct node {
    void *data;
    struct node *next;
  } *head;
};

Stack stack_create() {
  Stack stk;

  stk = (Stack)malloc(sizeof(struct Stack_T));
  if (stk == NULL) {
    return NULL;
  }

  stk->len = 0;
  stk->head = NULL;
  return stk;
}

int stack_is_empty(Stack stk) {
  assert(stk);

  return stk->len == 0;
}

void stack_push(Stack stk, void *data) {
  struct node *new_head;

  assert(stk);

  new_head = (struct node *)malloc(sizeof(struct node));
  if (new_head == NULL) {
    return;
  }

  new_head->data = data;
  new_head->next = stk->head;
  stk->head = new_head;
  stk->len++;
}

void *stack_pop(Stack stk) {
  struct node *old_head;
  void *inner_data;

  assert(stk);
  assert(stk->len > 0);

  old_head = stk->head;
  stk->head = old_head->next;
  stk->len--;

  inner_data = old_head->data;
  free(old_head);
  return inner_data;
}

void stack_free(Stack *stk) {
  struct node *cur, *next;

  assert(stk);
  assert(*stk);

  for (cur = (*stk)->head; cur != NULL; cur = next) {
    next = cur->next;
    free(cur);
  }

  free(*stk);
  *stk = NULL;
}
