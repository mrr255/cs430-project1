// We begin by including some standard C headers:
#include <stdlib.h>
#include <stdio.h>

//main method
int main(int argc, char *argv[]) {

  // check for appropriate arguments
  if (argc != 4) {
    fprintf(stderr, "Usage: ppmrw typenum input.ppm output.ppm\n");
    return(1);
  }

  FILE* fh = fopen(argv[2], "r");
  FILE* fw = fopen(argv[3], "w");

  fprintf(fw, "P%s\n",argv[1]);

  int c = fgetc(fh);
  if (c != 'P')
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
  c = fgetc(fh);
  if( c == '3')
  printf("Type 3\n");
  else if( c == '6'){
  printf("Type 6\n");
  //fprintf(fw, "P6\n");
}
  else
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");

  c = fgetc(fh);
  printf("%c\n", c);
  if (c != '\n')
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
  c = fgetc(fh);
  int d;
  while (c == '#'){
    fprintf(fw,"%c", c);
    d = fgetc(fh);
    fprintf(fw,"%c", d);
    while (d!= '\n'){
      d = fgetc(fh);
      fprintf(fw,"%c", d);
    }
      //fprintf(fw,"\n");
      c = fgetc(fh);
    }

    printf("%s\n", "Height");
    printf("%c\n", c);
    char *height;
    height = malloc(16 * 5);
    int i = 0;
    while(c != ' '){
      height[i] = c;
      c = fgetc(fh);
      printf("%c\n", c);
      i+=1;
    }
      int h = atoi(height);

      printf("%s\n", "width");
    char *width;
    width = malloc(16 * 5);
    i = 0;
    while(c != '\n'){
      width[i] = c;
      c = fgetc(fh);
      printf("%c\n", c);
      i+=1;
    }
    int w = atoi(width);
    printf("%i\n",h);
    printf("%i\n",w);

    fprintf(fw, "%i ", h);
    fprintf(fw, "%i\n", w);

    printf("%s\n", "maxColor");
    char *maxColor;
    maxColor = malloc(16 * 5);
    i = 0;
    c = fgetc(fh);
    while(c != '\n'){
      maxColor[i] = c;
      printf("%c\n", c);
      i+=1;
      c = fgetc(fh);
    }
    int mC = atoi(maxColor);
    printf("%i\n",mC);
    fprintf(fw,"%i\n",mC);


return (0);
}
