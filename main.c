#include "include/atom.h"
#include <limits.h>
#include <stdio.h>

/*
*  Used for isolated debugging outside of valgrind
*  and test environment.
*/

int main() {
  const char *min = atom_int(LONG_MIN);
  const char *max = atom_int(LONG_MAX);

  printf("%s\n", min);
  printf("%s", max);
}
