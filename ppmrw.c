// We begin by including some standard C headers:
#include <stdlib.h>
#include <stdio.h>

//main method
int main(int argc, char *argv[]) {

  // check for appropriate arguments
  if (argc != 4) {
    fprintf(stderr, "Usage: ppmrw typenum input.ppm output.ppm w h\n");
    return(1);
  }

  FILE* fh = fopen(argv[2], "r");
  int c = fgetc(fh);
  if (c != 'P')
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
  c = fgetc(fh);
  if( c == '3')
  printf("Type 3");
  else if( c == '6')
  printf("Type 6");
  else
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
return (0);
}
