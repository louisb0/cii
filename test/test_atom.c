#include "../include/atom.h"
#include <criterion/criterion.h>
#include <limits.h>
#include <signal.h>

Test(atom, atom_expected_string_behaviour) {
  char str[] = "test";

  const char *one = atom_string(str);
  const char *two = atom_string(str);

  cr_assert_eq(one, two);
  cr_assert_neq(one, str);
}

Test(atom, atom_expected_int_behaviour) {
  const char *one = atom_int(1);
  const char *two = atom_int(1);

  cr_assert_eq(one, two);
}

Test(atom, atom_expected_len_behaviour) {
  char str[] = "test";

  const char *one = atom_int(1);
  const char *two = atom_string(str);

  cr_assert_eq(atom_length(one), 1);
  cr_assert_eq(atom_length(two), 4);
}

Test(atom, atom_null_string, .signal = SIGABRT) { atom_string(NULL); }

Test(atom, atom_min_max_int) {
  const char *min = atom_int(LONG_MIN);
  const char *max = atom_int(LONG_MAX);

  cr_assert_neq(min, max);
}
