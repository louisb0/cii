#ifndef EXCEPT_H
#define EXCEPT_H

#include <setjmp.h>

typedef struct except_t {
  char *reason;
} except_t;

typedef struct except_frame except_frame;
struct except_frame {
  except_frame *prev;
  jmp_buf env;

  const except_t *exception;
  const char *file;
  int line;
};

extern except_frame *except_stack;

enum { except_entered = 0, except_raised, except_handled, except_finalised };

void except_raise(const except_t *exception, const char *file, int line);

#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)
#define RERAISE                                                                \
  except_raise(except_frame.exception, except_frame.file, except_frame.line)

#define RETURN                                                                 \
  switch (except_stack = except_stack->prev, 0)                                \
  default:                                                                     \
    return

#define TRY                                                                    \
  do {                                                                         \
    volatile int except_flag;                                                  \
    except_frame except_frame;                                                 \
    except_frame.prev = except_stack;                                          \
    except_stack = &except_frame;                                              \
    except_flag = setjmp(except_frame.env);                                    \
    if (except_flag == except_entered) {

#define EXCEPT(e)                                                              \
  if (except_flag == except_entered)                                           \
    except_stack = except_stack->prev;                                         \
  }                                                                            \
  else if (except_frame.exception == &(e)) {                                   \
    except_flag = except_handled;

#define ELSE                                                                   \
  if (except_flag == except_entered)                                           \
    except_stack = except_stack->prev;                                         \
  }                                                                            \
  else {                                                                       \
    except_flag = except_handled;

#define FINALLY                                                                \
  if (except_flag == except_entered)                                           \
    except_stack = except_stack->prev;                                         \
  }                                                                            \
  {                                                                            \
    if (except_flag == except_entered)                                         \
      except_flag = except_finalised;

#define END_TRY                                                                \
  if (except_flag == except_entered)                                           \
    except_stack = except_stack->prev;                                         \
  }                                                                            \
  if (except_flag == except_raised)                                            \
    RERAISE;                                                                   \
  }                                                                            \
  while (0)

#endif // EXCEPT_H
