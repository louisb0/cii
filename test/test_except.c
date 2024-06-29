#include "../include/except.h"
#include <criterion/criterion.h>
#include <signal.h>

Test(except, except_standard) {
  except_t e1 = { "Exception" };
  volatile int caught = 0;

  TRY
    RAISE(e1);
  EXCEPT(e1)
    caught = 1;
  END_TRY;

  cr_assert_eq(caught, 1);
}

Test(except, except_multi_standard) {
  except_t e1 = { "Exception" };
  except_t e2 = { "Exception" };
  volatile int caught = 0;

  TRY
    RAISE(e2);
  EXCEPT(e1)
    caught = 0;
  EXCEPT(e2)
    caught = 1;
  END_TRY;

  cr_assert_eq(caught, 1);
}


Test(except, except_else_standard) {
  except_t e1 = { "Exception" };
  except_t e2 = { "Exception" };
  volatile int caught = 0;

  TRY
    RAISE(e2);
  EXCEPT(e1)
    caught = 0;
  ELSE
    caught = 1;
  END_TRY;

  cr_assert_eq(caught, 1);
}


Test(except, except_finally_standard) {
  except_t e1 = { "Exception" };
  volatile int finally = 0;

  TRY
    RAISE(e1);
  EXCEPT(e1)
    finally = 0;
  FINALLY
    finally = 1;
  END_TRY;

  cr_assert_eq(finally, 1);
}

Test(except, except_else_finally_standard) {
  except_t e1 = { "Exception" };
  except_t e2 = { "Exception" };
  volatile int else_ = 0;
  volatile int finally = 0;

  TRY
    RAISE(e2);
  EXCEPT(e1)
    else_ = 0;
    finally = 0;
  ELSE
    else_ = 1;
  FINALLY
    finally = 1;
  END_TRY;

  cr_assert_eq(else_, 1);
  cr_assert_eq(finally, 1);
}

Test(except, except_uncaught, .signal = SIGABRT) {
  except_t e1 = { "Exception" };

  TRY
    RAISE(e1);
  END_TRY;
}
