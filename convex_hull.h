// Ioannis Katsavounidis, Feb. 2019
#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  double bitrate;
  double distortion;
  int reference;
} RDpoint;

int convex_hull(RDpoint *rd_vector_in, int size_in, RDpoint *rd_vector_out);

#endif /* CONVEX_HULL_H */
