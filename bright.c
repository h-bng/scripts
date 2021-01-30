#include <stdio.h>
#include <stdlib.h>

/* CHANGE THESE FOR YOUR OWN SYSTEM */
#define B_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MIN_B 9
#define MAX_B 937

#define B2X(B) (B*100/MAX_B)
#define X2B(X) (X*MAX_B/100)

int main (int argc, char* argv[])
{
  FILE* fp;
  int b, db;

  if ((fp = fopen (B_PATH, "r")) == NULL) {
    perror (B_PATH);
    return -1;
  }

  if (fscanf (fp, "%d", &b) == EOF) {
    perror (B_PATH);
    return -1;
  }
  
  fclose (fp);

  if (argc == 1) {
    printf ("%f\n", B2X((float)b));
    return 0;
  }

  if ((fp = fopen (B_PATH, "w")) == NULL) {
    perror (B_PATH);
    return -1;
  }
  
  db = X2B(atof(argv[1]));
  
  if (argv[1][0] == '+' || argv[1][0] == '-')
    db += b;
  
  if (db > MAX_B)
    db = MAX_B;

  if (db < MIN_B)
    db = MIN_B;
      
  if (fprintf (fp, "%d", db) < 0) {
    perror (B_PATH);
    return -1;
  }

  fclose (fp);
  return 0;
}
