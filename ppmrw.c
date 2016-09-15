//ppmrw.c
//Matthew Robertson
//CS430 Project 1


// Header Includes:
#include <stdlib.h>
#include <stdio.h>

//Main Method
int main(int argc, char *argv[]) {

// Check for appropriate arguments
  if (argc != 4) {
    fprintf(stderr, "Usage: ppmrw typenum input.ppm output.ppm\n");
    return(1);
  }
//Open File Handles
  FILE* fr = fopen(argv[2], "r"); // File Read
  FILE* fw = fopen(argv[3], "w"); // File Write

//Parse Header
  int c = fgetc(fr); // Get 'P'
  if (c != 'P')
    {
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
    return(1);
    }
  c = fgetc(fr); // Get 'X' -- Should be 3 or 6
  if( c == '3')
    {
    //printf("Type 3\n"); //Debug Output
    }
  else if( c == '6')
    {
    //printf("Type 6\n"); //Debug Output
    }
  else
    {
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
    return(1);
    }

  fprintf(fw, "P%s\n",argv[1]); //Print the P'X' portion of the header to the output file

  c = fgetc(fr); //Get '\n'
  //printf("%c\n", c); //Debug Output

  if (c != '\n')
    {
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
    return(1);
    }
  c = fgetc(fr); //Get Next character -- should be comment, or width/height
  int d; //comment character variable
  while (c == '#') //Process the comment line(s)
    {
    fprintf(fw,"%c", c); //write the # to the output file
    d = fgetc(fr);
    fprintf(fw,"%c", d);
    while (d!= '\n') //Write the rest of the comment to the output file
      {
      d = fgetc(fr);
      fprintf(fw,"%c", d);
      }
      c = fgetc(fr); //Get next char -- either # or width/height
    }

  //Parse Height/Width
  //printf("%s\n", "Height"); //Debug Output
  //printf("%c\n", c); //Debug Output

  char *height; //Create array to hold characters of the height
  height = malloc(16 * 5);
  int i = 0;
  while(c != ' ') //Get all characters before the first space
    {
    height[i] = c; //Add them to the array
    c = fgetc(fr);
    //printf("%c\n", c); //Debug Output
    i+=1;
    }
  int h = atoi(height); //Convert character array to an Integer value


  //printf("%s\n", "width"); //Debug Output

  char *width; //Create array to hold characters of the width
  width = malloc(16 * 5);
  i = 0;
  while(c != '\n') //Get all characters before the end of the line
    {
    width[i] = c; //Add them to the array
    c = fgetc(fr);
    //printf("%c\n", c); //Debug Output
    i+=1;
    }
  int w = atoi(width); //Convert character array to an Integer value

  //printf("%i\n",h); //Debug Output
  //printf("%i\n",w); //Debug Output

  //Write the Image size to the output file
  fprintf(fw, "%i ", h);
  fprintf(fw, "%i\n", w);

  //Parse Max Color Value
  //printf("%s\n", "maxColor"); //Debug Output

  char *maxColor; //Create array to hold characters of the max color
  maxColor = malloc(16 * 5);
  i = 0;
  c = fgetc(fr);
  while(c != '\n') //Get all characters before the end of the line
    {
    maxColor[i] = c; //Add them to the array
    //printf("%c\n", c); //Debug Output
    i+=1;
    c = fgetc(fr);
    }
  int mC = atoi(maxColor); //Convert character array to an Integer value

  //printf("%i\n",mC); //Debug Output

  //Write the max color to the output file
  fprintf(fw,"%i\n",mC);


return (0);
}
