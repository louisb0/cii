#ifndef STACK_H
#define STACK_H

typedef struct Stack_T *Stack;

Stack   stack_create();
int     stack_is_empty(Stack s);
void    stack_push(Stack s, void *data);
void   *stack_pop(Stack s);
void    stack_free(Stack *s);

#endif // STACK_H
