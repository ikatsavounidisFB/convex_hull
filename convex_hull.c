// Ioannis Katsavounidis, Feb. 2019
#include "convex_hull.h"

// Compares 2 (R,D) points in increasing order of bitrate
int compar(const void *p1, const void *p2)
{
  RDpoint *x = (RDpoint *) p1;
  RDpoint *y = (RDpoint *) p2;

  if(x->bitrate < y->bitrate)
    return -1;
  else if(x->bitrate > y->bitrate)
    return 1;
  else if(x->distortion < y->distortion)
    return -1;
  else if(x->distortion > y->distortion)
    return 1;

  return 0;
}

// Returns positive value if p1->p2->p3 has a clockwise turn
// Negative value if p1->p2->p3 has a counter-clockwise turn
// 0 value if they are aligned
double cross_product(RDpoint *p1, RDpoint *p2, RDpoint *p3)
{
  return (p2->bitrate - p1->bitrate) * (p3->distortion - p1->distortion) -
         (p2->distortion - p1->distortion) * (p3->bitrate - p1->bitrate);
}

// Calculate and copy the points in rd_vector_in that are on the *lower* convex hull
// Returns number of points on the convex hull (effective size of rd_vector_out)
// C-version of the Monotone chain algorithm - complexity O(nlogn)
int convex_hull(RDpoint *rd_vector_in, int size_in, RDpoint *rd_vector_out)
{
  int i, k = 0;

  // First, order RD-points in increasing bitrate
  qsort((void *) rd_vector_in, size_in, sizeof(rd_vector_in[0]), compar);

  for (i = 0; i < size_in; i++) {
    // Second, skip points that have higher distortion AND higher bitrate
    if (k >= 1 && rd_vector_in[i].distortion >= rd_vector_out[k-1].distortion) continue;
    // Finally remove the last point(s) in out, if the new one is shadowing
    while (k >= 2 && cross_product(&rd_vector_out[k-2], &rd_vector_out[k-1], &rd_vector_in[i]) <= 0) k--;
    // We have reached a point that is on the convex hull - add it
    memcpy(&rd_vector_out[k], &rd_vector_in[i], sizeof(rd_vector_in[0]));
    k++;
  }

  return k;
}
