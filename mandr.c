/* random center and mag */
#include <stdio.h>

#define SIZEX 79
#define SIZEY 48
#define THRESHOLD 128
#define RMAX 32768

int test (r, i) double r; double i;
{
   double dr = r;
   double di = i;
   double odr;
   int t;

   for (t=0; t<THRESHOLD; t++)
   {
      odr = dr;
      dr = (dr * dr - di * di);
      di = (odr * di + di * odr);

      dr += r;
      di += i;
      if (dr*dr+di*di > 4.)
      {
         return t;
      }
   }

   return -1;
}

int setview(xmin, xmax, ymin, ymax) double* xmin; double* xmax; double* ymin; double* ymax;
{
   double centerr, centeri, mag;

   long stvec;
   int k;

   time(&stvec);
   k = stvec;
   srand(k);
   printf("\n");
   printf("Seed: %d ",k);

   centerr = -1.5 + 2. * (double) rand() / RMAX;
   centeri = -1. + 2. * (double) rand() / RMAX;
   mag = 0.66 + 8. * (double) rand() / RMAX;

   printf("Center: (%f,%f)  Mag: %f\n",centerr,centeri,mag);

   *xmin = -1.0 / mag + centerr;
   *xmax = 1.0 / mag + centerr;
   *ymin = -1.0 / mag + centeri;
   *ymax = 1.0 / mag + centeri;

   printf("Mandelbrot Set (%f, %f) to (%f, %f)\n",*xmin,*ymin,*xmax,*ymax);

   return 0;
}


int main(argc, argv) int argc; char** argv;
{
   double xmin, xmax, ymin, ymax;
   double dx, dy, x, y;
   int cx, cy;
   int i;

   setview(&xmin,&xmax,&ymin,&ymax);
/*
   printf("%c",12);
*/
   printf("\n\n\n");

   dx = (xmax - xmin) / SIZEX;
   dy = (ymax - ymin) / SIZEY;

   x = xmin;
   y = ymax;

   for (cy=0; cy<SIZEY; cy++)
   {
      for (cx=0; cx<SIZEX; cx++)
      {
          int v = test(x,y);
          printf(v >= 0 ? "%c" : " ",(v % 63)+33);

          x += dx;
      }
      x = xmin;
      y -= dy;
      printf("\n");
   }

/*
   printf("\n\nMandelbrot Set (%f, %f) to (%f, %f)\n",xmin,ymin,xmax,ymax);
*/
   printf("%c",12);   /* form feed */

   return 0;

}
