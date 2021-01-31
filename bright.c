/* 
 * bright.c: an inefficient way to change screen brightness
 *
 * change B_PATH for your own system.
 * set MAX_B and MIN_B to desired values.
 *
 * usage:
 * bright      get current brightness
 * bright  B   set brightness to B%
 * bright +b   increase brightness by b%
 * bright -b   decrease brightness by b%
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define B_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MIN_B 9
#define MAX_B 937

#define B2X(B) (B*100/MAX_B)
#define X2B(X) (X*MAX_B/100)

void die (void)
{
  perror (B_PATH);
  exit (1);
}

int main (int argc, char* argv[])
{
  FILE* fp;
  int b, db;

  if ((fp = fopen (B_PATH, "r")) == NULL) die ();

  if (fscanf (fp, "%d", &b) == EOF) die ();
  
  fclose (fp);

  if (argc == 1) {
    printf ("%f\n", B2X((float)b));
    return 0;
  }

  if ((fp = fopen (B_PATH, "w")) == NULL) die ();
  
  db = X2B(atof(argv[1]));
  
  if (argv[1][0] == '+' || argv[1][0] == '-')
    db += b;
  
  if (db > MAX_B)
    db = MAX_B;
  else if (db < MIN_B)
    db = MIN_B;
      
  if (fprintf (fp, "%d", db) < 0) die ();

  fclose (fp);
  return 0;
}
