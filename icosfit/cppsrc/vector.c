#include "vector.h"
#include "nl.h"

ICOS_Float *vector(int N) {
  ICOS_Float *rv = (ICOS_Float*)new_memory(N*sizeof(ICOS_Float));
  return rv;
}

void free_vector(ICOS_Float *vec) {
  free_memory((void *)vec);
}
