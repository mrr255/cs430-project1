//ppmrw.c
//Matthew Robertson
//CS430 Project 1


//Header Includes:
#include <stdlib.h>
#include <stdio.h>

//Define Structures
typedef struct Pixel
  {
  unsigned char r, g, b;
  } Pixel;

// Helper method to parse from Ascii
int getAscii(FILE *fr, char *temp, FILE *fw)
  {
  int c = fgetc(fr);
  int i = 0;
  while(c != '\n' && c != ' ' && c != '\t') //Collect all characters before whitespace
    {
    temp[i]=c; //Add it to a buffer
    i+=1;
    c = fgetc(fr);
    if(i>3)
      {
      fprintf(stderr, "%s\n", "Error: file not of type declared in format header");
      exit(1);
      }
    }
  int t = atoi(temp); //Convert to an integer

  if(t > 255)
    {
    fprintf(stderr, "%s\n", "Error: multibyte color is not supported.");
    return(1);
    }
  //printf("%i", t); //Debug Output
  return(t);
  }

//Helper method to parse from Raw data
int getByte(FILE *fr, char *temp, FILE *fw)
  {
  int c = fgetc(fr); //Grab next character
  if(c == ' ' || c == '\n')
  {
  fprintf(stderr, "%s\n", "Error: file not of type declared in ppm header.");
  exit(1);
  }
  int t = (int) c; //Store as an int

  if(t > 255)
    {
    fprintf(stderr, "%s\n", "Error: multibyte color is not supported.");
    return(1);
    }
  //printf("%i", t);//Debug Output
  return(t);
  }

//Main Method
int main(int argc, char *argv[])
  {

  //Check for appropriate number of arguments
  if (argc != 4)
    {
    fprintf(stderr, "Usage: ppmrw typenum input.ppm output.ppm\n");
    return(1);
    }

  //Open File Handles
  FILE* fr = fopen(argv[2], "r"); // File Read
  FILE* fw = fopen(argv[3], "w"); // File Write

  //Check if input file exists
  if(fr == NULL)
    {
    fprintf(stderr, "%s\n", "Error: input file type not found.");
    return(1);
    }

  //Check if output file type is supported
  int destType = atoi(argv[1]);
  if(destType != 3 && destType != 6)
    {
    fprintf(stderr, "%s\n", "Error: output file type not supported.");
    return(1);
    }
  //printf("%i\n", destType); //Debug output


  //Parse Header
  int c = fgetc(fr); // Get 'P'
  int fileType = 0;
  if (c != 'P')
    {
    fprintf(stderr, "%s\n", "Error: file not of type ppm or header not formatted correctly.");
    return(1);
    }
  c = fgetc(fr); // Get 'X' -- Should be 3 or 6
  if( c == '3')
    {
    fileType = 3;
    //printf("Type 3\n"); //Debug Output
    }
  else if( c == '6')
    {
    fileType = 6;
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

  if (c != '\n' && c!= ' ' && c!= '\t')
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

  if(mC > 255)
    {
    fprintf(stderr, "%s\n", "Error: multibyte color is not supported.");
    return(1);
    }
  //printf("%i\n",mC); //Debug Output

  //Write the max color to the output file
  fprintf(fw,"%i\n",mC);


  //Parsing of image data
  Pixel *image;
  image = malloc(sizeof(Pixel) * w * h); //Prepare memory for image data
  unsigned char temp[32]; //Create buffer for data

  if (fileType == 3) //Collect Ascii Image data
    {
    int row, col;
    for (row = 0; row < h; row += 1)
      {
      for (col = 0; col < w; col += 1) //Itterate through the image and add it to the structures
        {
        image[w*row + col].r = getAscii(fr,temp,fw);
        //printf("%d ", image[w*row + col].r); //Debug Output
        image[w*row + col].g = getAscii(fr,temp,fw);
        //printf("%d ", image[w*row + col].g); //Debug Output
        image[w*row + col].b = getAscii(fr,temp,fw);
        //printf("%d  ", image[w*row + col].b); //Debug Output
        }
      //printf("\n"); //Debug Output
      }
    }
  else //Collect Raw Image data
    {
    int row, col;
    for (row = 0; row < h; row += 1)
      {
      for (col = 0; col < w; col += 1) //Itterate through the image and add it to the structures
        {
        image[w*row + col].r = getByte(fr,temp,fw);
        //printf("%i ", image[w*row + col].r); //Debug Output
        image[w*row + col].g = getByte(fr,temp,fw);
        //printf("%i ", image[w*row + col].g); //Debug Output
        image[w*row + col].b = getByte(fr,temp,fw);
        //printf("%i  ", image[w*row + col].b); //Debug Output
        }
      //printf("\n"); //Debug Output
      }

  }


// Print image data to the output file in either ascii of Raw Data
  if(destType == 3) //Ascii
    {
    int row, col;
    for (row = 0; row < h; row += 1)
      {
      for (col = 0; col < w; col += 1)
        {
        fprintf(fw,"%i\n", image[w*row + col].r);
        fprintf(fw, "%i\n", image[w*row + col].g);
        fprintf(fw, "%i\n", image[w*row + col].b);
        }
      }
    }
  else if(destType == 6) //Raw data
    {
    fwrite(image,sizeof(Pixel),w*h,fw);
    }
  else
    {
    fprintf(stderr, "%s\n", "Error: output file type not supported.");
    return(1);
    }
  fclose(fw);
  fclose(fr);
  return (0);
  }
