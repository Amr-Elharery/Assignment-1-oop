#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage();
void saveImage();
void menu();
void showOptions();
void bwFilter();
void Invert();
void Merge();
void Flip(char mode);
void Lighten();
void Darken();
void Rotate();
void Blur();

int main()
{
  loadImage();
  menu();

  return 0;
}

// Options
void showOptions()
{

  cout << "Please select a filter to apply or 0 to exit:\n";
  cout << "1-	Black & White Filter\n";
  cout << "2-	Invert Filter\n";
  cout << "3-	Merge Filter\n";
  cout << "4-	Flip Image\n";
  cout << "5-	Darken and Lighten Image\n";
  cout << "6-	Rotate Image\n";
  cout << "c-	Blur Image\n";
}

// Menu

void menu()
{
  char ch;
  showOptions();
  cin >> ch;

  while (ch)
  {
    if (ch == '0')
    {
      cout << "Exit done\n";
      break;
    }

    else if (ch == '1')
      bwFilter();

    else if (ch == '2')
      Invert();

    else if (ch == '3')
    {
      char imageFileName[100];

      // Get gray scale image file name
      cout << "Please enter name of image file to merge with: ";
      cin >> imageFileName;

      // Add to it .bmp extension and load image
      strcat(imageFileName, ".bmp");
      readGSBMP(imageFileName, image2);
      Merge();
    }

    else if (ch == '4')
    {
      char mode;
      cout << "Flip (h)orizontally or (v)ertically ?\n";
      cin >> mode;
      Flip(mode);
    }

    else if (ch == '5')
    {
      char mode;
      cout << "Do you want to (d)arken or (l)ighten ?\n";

      cin >> mode;

      if (mode == 'l')
        Lighten();
      if (mode == 'd')
        Darken();
    }

    else if (ch == '6')
      Rotate();

    else if (ch == 'c')
      Blur();

    showOptions();
    cin >> ch;
  }
}

//_________________________________________
void loadImage()
{
  char imageFileName[100];

  // Get gray scale image file name
  cout << "Enter the source image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage()
{
  char imageFileName[100];

  // Get gray scale image target file name
  cout << "Enter the target image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  writeGSBMP(imageFileName, image);
}

//_________________________________________
// Black & White
void bwFilter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {

      if (image[i][j] > 100)
        image[i][j] = 255;
      else
        image[i][j] = 0;
    }
  }

  saveImage();
}

// Invert
void Invert()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {

      image[i][j] = 255 - image[i][j];
    }
  }
  saveImage();
}

// Merge
void Merge()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image[i][j] = (image[i][j] + image2[i][j]) / 2;
    }
  }
  saveImage();
}

// Flip
void Flip(char mode)
{
  if (mode == 'v')
  {
    for (int i = 0; i < SIZE / 2; i++) // for loop to iterate  half of the rows in image
    {
      for (int j = 0; j < SIZE; j++) // for loop to iterate all the columns in the image
      {
        unsigned char temp = image[i][j]; // creat unsigned char to store the pixel of the left part to put it in the right pixel

        image[i][j] = image[SIZE - 1 - i][j]; // put the right pixel in the left pixel

        image[SIZE - 1 - i][j] = temp; // put the left pixel to the right pixel
      }
    }
    saveImage();
  }
  else if (mode == 'h')
  {
    for (int i = 0; i < SIZE; i++) // for loop to iterate  all rows in image
    {
      for (int j = 0; j < SIZE / 2; j++) // for loop to iterate half of the columns in the image
      {
        unsigned char temp = image[i][j]; // creat unsigned char to store the pixel of the upper part to put it in the lower pixel

        image[i][j] = image[i][SIZE - 1 - j]; // put the lower pixel in the upper pixel

        image[i][SIZE - 1 - j] = temp; // put the upper pixel to the lower pixel
      }
    }
    saveImage();
  }
}
// Lighten

void Lighten()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (image[i][j] <= 190)
        image[i][j] += 65;
    }
  }
  saveImage();
}

// Darken

void Darken()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {

      image[i][j] = image[i][j] / 2;
    }
  }
  saveImage();
}

// Rotate
void Rotate()
{
  int rotate;
  cout << "Rotate (90), (180) or (360) degrees? ";
  cin >> rotate;

  if (rotate == 90) // in case of 90 degrees
  {

    unsigned char tempImage[SIZE][SIZE];

    memcpy(tempImage, image, SIZE * SIZE * sizeof(unsigned char)); // Create a temporary image array and copy the original image

    for (int i = 0; i < SIZE; i++) // for loop to iterate  all rows in image
    {
      for (int j = 0; j < SIZE; j++) // for loop to iterate all the columns in the image
      {

        image[j][SIZE - 1 - i] = tempImage[i][j]; // the row and column indices swapped and the column index reversed
      }
    }
  }
  saveImage(); // Save the rotated image
}

void Blur()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image[i][j] = (image[i][j] + image[i + 2][j + 2]) / 2;
    }
  }
  saveImage();
}