#include "../include/stack.h"
#include <signal.h>
#include <criterion/criterion.h>

Test(stack, stack_create) {
  Stack s = stack_create();

  cr_assert_not_null(s);
  cr_assert(stack_is_empty(s));

  stack_free(&s);
}

Test(stack, stack_push_pop) {
  Stack s = stack_create();

  stack_push(s, (void *)1);
  cr_assert_not(stack_is_empty(s));
  cr_assert_eq((int *)stack_pop(s), 1);
  cr_assert(stack_is_empty(s));

  stack_free(&s);
}

Test(stack, stack_free) {
  Stack s = stack_create();

  stack_push(s, (void *)1);
  stack_free(&s);

  cr_assert_null(s);
}

Test(stack, stack_out_of_bounds, .signal = SIGABRT) {
  Stack s = stack_create();

  stack_pop(s);
}
