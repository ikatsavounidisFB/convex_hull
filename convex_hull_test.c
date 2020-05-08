// Ioannis Katsavounidis, Feb. 2019
// This code is available to anyone who wants to use it, for free
#include <stdio.h>
#include "convex_hull.h"

int main(int argc, char *argv[]) {
   RDpoint *in;
   RDpoint *out;
   static const int size = 10;
   double rates[size] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
   double PSNR[size] = {30.0, 31.0, 31.5, 32.4, 32.9, 33.7, 34.2, 34.9, 35.4, 36.0};
   int size_out;
   int i;

   in = (RDpoint *) malloc(size*sizeof(in[0]));
   if (in == NULL)
      exit(-1);
   out = (RDpoint *) malloc(size*sizeof(out[0]));
   if (out == NULL)
      exit(-1);

   for(i = 0; i < size; i++) {
      in[i].bitrate = rates[i];
      // Since we calculate lower convex hull, we invert quality to distortion
      in[i].distortion = -PSNR[i];
      in[i].reference = i;
   }

   size_out = convex_hull(in, size, out);

   out = (RDpoint *) realloc(out, size_out * sizeof(out[0]));

   printf("Convex Hull (%d points):\n", size_out);
   for(i=0; i< size_out; i++) {
      // Invert back distortion to quality for printing
      printf("i=%d, Rate=%lf, PSNR=%lf\n",
             out[i].reference, out[i].bitrate, -out[i].distortion);
   }

   if (out != NULL)
      free(out);

   free(in);

   return 0;
}
