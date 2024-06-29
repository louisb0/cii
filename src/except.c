#include "../include/except.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

except_frame *except_stack = NULL;

void except_raise(const except_t *exception, const char *file, int line) {
  except_frame *p = except_stack;

  assert(exception);

  if (p == NULL) {
    fprintf(stderr, "Uncaught exception");
    if (exception->reason)
      fprintf(stderr, " %s", exception->reason);
    else
      fprintf(stderr, " at 0x%p", exception);
    if (file && line > 0)
      fprintf(stderr, " raised at %s:%d\n", file, line);
    fflush(stderr);
    abort();
  }
  p->exception = exception;
  p->file = file;
  p->line = line;
  except_stack = except_stack->prev;

  longjmp(p->env, except_raised);
}
