// Simple Mandelbrot generator modified for Julia set calculations
// May 17, 2019
// December 1, 2019 now with arguments
// June 4, 2021 character set and dimensions for Qume Spring 11/55

/* The Mandelbrot set iterates z_{n+1} = z_n^2 + c
   where c is complex and z_0 = 0.
   The Julia set iteratues the same function, but with different (complex) starting values of z_0
   for each value c.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  int x, y;
  int i, iterations;
  double cRe, cIm;
  double mag;
  double scaleRe, scaleIm;
  double halfcolumns, halfrows;
  double D, C, A, B, T;

  /* For the Qume AT&T ASCII print wheel, these are the printable characters... */
  char printstr[] = "!\"#$%&\')+,-./0123456789:;<=?ABCDEFGHJKMNOPQRSTUVWYZ\\^abcdfghijklmnopqrstuvwxyz{}";
  //                 ! "#$%& ')+,-./0123456789:;<=?ABCDEFGHJKMNOPQRSTUVWYZ \^abcdfghijklmnopqrstuvwxyz{}
  //char printstr[] = "MandElbrot";

  /* print the printable characters (commented out) */
  /*
  printf("\n");
  for (i=0;i<=strlen(printstr);i++) printf("%c",printstr[i]);
  printf("\n");
  */

  //to-do: set these as definitions...
  halfcolumns = 158/2; /* Prestige Elite wheel is 12 characters / inch = 158 characters */
  halfrows = 36;       /* set at 8 rows / in - 4 row margins on top and bottom */

  scaleRe = 2.0/halfcolumns;
  //  scaleIm = 1.66*scaleRe;
  scaleIm = 1.5*scaleRe;

  // eventually accept input here
  if (argc < 2) {
    cRe = 0.;
    cIm = 0;
    mag = 1.;
  }
  else if (argc >= 3 && argc <= 4) {
    cRe = strtod(argv[1],NULL);
    cIm = strtod(argv[2],NULL);
    mag = 1;
    if (argc == 4)
      mag = strtod(argv[3],NULL);
  }
  else {
    printf("Usage: mbrot [centerRe centerIm] [mag]\n");
    printf("Interesting values:\n");
    printf("  -0.46714 0.63632 50\n");
    printf("  -0.1528  1.0397  100\n");
    printf("  -1.25    0.05    2\n");
    return 0;
  }

  iterations = 100;

  //  printf("\n\n\n\n\n");
  for (y=halfrows; y>-halfrows; y--){
    D=y*scaleIm/mag;
    for (x=-halfcolumns; x<halfcolumns; x++){
      C = x*scaleRe/mag;
      A=C; B=D;
      i=0;
      while (i <= iterations){
        if ((A*A+B*B)>4){
	  //          printf("%c",(i % 63)+33); /* for ASCII-63 */
	  	  printf("%c",(printstr[i % strlen(printstr)]));
 	  //printf(" ");
          break; /* leave the iterations */
        }
        else{
          T=A*A-B*B+cRe;
          B=2*A*B+cIm;
          A=T;
        }
        i++;
      }
      if(i>iterations){
        printf(" ");
	//printf("#");
      }
    }
    printf("\r\n");
  }
  printf("\n\nJulia from %+f%+fi TO %+f%+fi\r\n",
         -halfcolumns*scaleRe/mag,
         halfrows*scaleIm/mag,
         halfcolumns*scaleRe/mag,
         -halfrows*scaleIm/mag);
  printf("c =  %+f%+fi, magnification: %f\n",
         cRe, cIm, mag);
  printf("\f");
}
