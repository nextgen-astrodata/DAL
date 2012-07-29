#include "Python.h"
#include <stdio.h>

int main( int argc, char**argv ) {
  (void)argc;
  (void)argv;

  printf("%u.%u", PY_MAJOR_VERSION, PY_MINOR_VERSION);

  return 0;
}

