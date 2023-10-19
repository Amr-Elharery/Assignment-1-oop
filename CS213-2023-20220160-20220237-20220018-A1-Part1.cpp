// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:CS213-2023-6-20220160-20220018-20220237-A1.cpp
// Last Modification Date:	19/10/2023
// Author1 and ID and Group: seif eldin shady abdelsalam , 20220160, b
// Author2 and ID and Group: Amr Tamer Samy , 20220237 , b
// Author3 and ID and Group: AHMED HUSSEIN SAAD, 20220018 , b
// Teaching Assistant:		xxxxx xxxxx
// Purpose: Learn how image processing work

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

unsigned char RGBImage[SIZE][SIZE][RGB];

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
void Edge();
void Enlarge();
void Shrink();
void MirrorImage();
void ShuffleImage();
void Blur();
void Crop();

void loadRGB()
{
  char imageFileName[100];

  // Get gray scale image file name
  cout << "Enter the source image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  readRGBBMP(imageFileName, RGBImage);
}

void saveRGB()
{
  char imageFileName[100];

  // Get gray scale image target file name
  cout << "Enter the target image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  writeRGBBMP(imageFileName, RGBImage);
}

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
  cout << "7-	Detect Image Edges\n";
  cout << "8-	Enlarge Image\n";
  cout << "9-	Shrink Image\n";
  cout << "a-	Mirror Image\n";
  cout << "b- ShuffleImage\n";
  cout << "c-	Blur Image\n";
  cout << "d- Crop Image\n";
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

    else if (ch == '7')
      Edge();

    else if (ch == '8')
      Enlarge();

    else if (ch == '9')
      Shrink();

    else if (ch == 'a')
      MirrorImage();

    else if (ch == 'b')
      ShuffleImage();

    else if (ch == 'c')
      Blur();
    else if (ch == 'd')
      Crop();
    else if (ch == 's')
      saveImage();

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
  cout << "Rotate (90), (180) or (270) degrees? ";
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

  else if (rotate == 180)
  {
    unsigned char tempImage2[SIZE][SIZE];

    memcpy(tempImage2, image, SIZE * SIZE * sizeof(unsigned char)); // Create a temporary image array and copy the original image

    for (int i = 0; i < SIZE; i++) // for loop to iterate  all rows in image
    {
      for (int j = 0; j < SIZE; j++) // for loop to iterate all the columns in the image
      {

        image[SIZE - 1 - i][SIZE - 1 - j] = tempImage2[i][j]; // the row and column indices reversed
      }
    }
  }

  else if (rotate == 270)
  {
    unsigned char tempImage3[SIZE][SIZE];

    memcpy(tempImage3, image, SIZE * SIZE * sizeof(unsigned char)); // Create a temporary image array and copy the original image

    for (int i = 0; i < SIZE; i++) // for loop to iterate  all rows in image
    {
      for (int j = 0; j < SIZE; j++) // for loop to iterate all the columns in the image
      {

        image[SIZE - 1 - j][i] = tempImage3[i][j]; // the row and column indices swapped
      }
    }
  }

  saveImage(); // Save the rotated image
}

// Edges
void Edge()
{
  int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  unsigned char tempImage[SIZE][SIZE];
  memcpy(tempImage, image, SIZE * SIZE);

  for (int i = 1; i < SIZE - 1; ++i)
  {
    for (int j = 1; j < SIZE - 1; ++j)
    {
      int gradientX = 0, gradientY = 0;
      for (int x = -1; x <= 1; ++x)
      {
        for (int y = -1; y <= 1; ++y)
        {
          gradientX += tempImage[i + x][j + y] * sobelX[1 + x][1 + y];
          gradientY += tempImage[i + x][j + y] * sobelY[1 + x][1 + y];
        }
      }
      int gradientMagnitude = sqrt(gradientX * gradientX + gradientY * gradientY);
      // Threshold the gradient magnitude to obtain binary edges (inverted)
      image[i][j] = (gradientMagnitude > 100) ? 0 : 255; // Inverted threshold
    }
  }
  saveImage();
}

// Enlarge
void Enlarge()
{
  unsigned char enlargedImage[SIZE][SIZE];

  memcpy(enlargedImage, image, SIZE * SIZE * sizeof(unsigned char));

  int quarterSize = SIZE / 2;
  int quarterRow, quarterCol;

  cout << "Enter the quarter to enlarge\n "
          " 1: Top-Left\n"
          " 2: Top-Right\n"
          " 3: Bottom-Left\n"
          " 4: Bottom-Right\n "
          " choose : ";
  int choice;
  cin >> choice;

  if (choice == 1)
  {
    quarterRow = 0;
    quarterCol = 0;
  }
  else if (choice == 2)
  {
    quarterRow = 0;
    quarterCol = quarterSize;
  }
  else if (choice == 3)
  {
    quarterRow = quarterSize;
    quarterCol = 0;
  }
  else if (choice == 4)
  {
    quarterRow = quarterSize;
    quarterCol = quarterSize;
  }
  else
  {
    cout << "Invalid choice" << endl;
    quarterRow = 0;
    quarterCol = 0;
  }

  for (int i = quarterRow; i < quarterRow + quarterSize; i++)
  {
    for (int j = quarterCol; j < quarterCol + quarterSize; j++)
    {
      enlargedImage[2 * i][2 * j] = image[i][j];
      enlargedImage[2 * i][2 * j + 1] = image[i][j];
      enlargedImage[2 * i + 1][2 * j] = image[i][j];
      enlargedImage[2 * i + 1][2 * j + 1] = image[i][j];
    }
  }

  // Copy the enlarged quarter back to the original image
  for (int i = quarterRow; i < quarterRow + quarterSize; i++)
  {
    for (int j = quarterCol; j < quarterCol + quarterSize; j++)
    {
      image[2 * i][2 * j] = enlargedImage[2 * i][2 * j];
      image[2 * i][2 * j + 1] = enlargedImage[2 * i][2 * j + 1];
      image[2 * i + 1][2 * j] = enlargedImage[2 * i + 1][2 * j];
      image[2 * i + 1][2 * j + 1] = enlargedImage[2 * i + 1][2 * j + 1];
    }
  }
  saveImage();
}

// Shrink
void Shrink()
{
  int shrinkFactor;
  cout << "Enter the shrink factor (e.g., 2 for half size): ";
  cin >> shrinkFactor;

  if (shrinkFactor <= 1)
  {
    cout << "Shrink factor should be greater than 1. No changes made." << endl;
    return;
  }

  int newSize = SIZE / shrinkFactor; // Calculate the new size of the image

  unsigned char shrunkImage[newSize][newSize]; // Create a new smaller image

  // Loop through the shrunk image
  for (int i = 0; i < newSize; i++)
  {
    for (int j = 0; j < newSize; j++)
    {
      // Calculate the average value in the original image for each pixel in the shrunk image
      int sum = 0;
      for (int x = i * shrinkFactor; x < (i + 1) * shrinkFactor; x++)
      {
        for (int y = j * shrinkFactor; y < (j + 1) * shrinkFactor; y++)
        {
          sum += image[x][y];
        }
      }
      shrunkImage[i][j] = static_cast<unsigned char>(sum / (shrinkFactor * shrinkFactor));
    }
  }

  // Copy the shrunk image back to the original image array
  for (int i = 0; i < newSize; i++)
  {
    for (int j = 0; j < newSize; j++)
    {
      image[i][j] = shrunkImage[i][j];
    }
  }

  // Save the shrunk image
  cout << "Image shrunk successfully." << endl;
  saveImage();
}

// Mirror Image
void MirrorImage()
{

  char choice;
  cout << "Choose an operation:\n"
       << "1 - Mirror Image Left\n"
       << "2 - Mirror Image Right\n"
       << "3 - Mirror Image Upper\n"
       << "4 - Mirror Image Lower\n";
  cin >> choice;

  if (choice == '1')
  {
    for (int i = 0; i < SIZE; i++)
    {
      int x = 1;
      for (int j = SIZE / 2; j < SIZE; j++)
      {
        image[i][j] = image[i][j - x];
        x = x + 2;
      }
    }
  }
  else if (choice == '2')
  {
    for (int i = 0; i < SIZE; ++i)
    {
      int x = 255;
      for (int j = 0; j < SIZE / 2; ++j)
      {
        image[i][j] = image[i][x];
        x--;
      }
    }
  }
  else if (choice == '3')
  {
    for (int i = 0; i < SIZE; i++)
    {
      int x = 1;
      for (int j = SIZE / 2; j < SIZE; j++)
      {
        image[j][i] = image[j - x][i];
        x = x + 2;
      }
    }
  }
  else
  {
    for (int i = 0; i < SIZE; ++i)
    {
      int x = 255;
      for (int j = 0; j < SIZE / 2; ++j)
      {
        image[j][i] = image[x][i];
        x--;
      }
    }
  }

  saveImage();
}
// ShuffleImage
void ShuffleImage()
{
  unsigned char image5[256][256] = {255}, image2[256][256] = {255}, image3[256][256] = {255}, image4[256][256] = {255}, image1[256][256] = {255};
  int a, b, c, d;
  cout << "Please enter the order you want to shuffle the image with as follows: \n";
  cout << "x - y - z - l\n";
  cout << "1 is the top left corner,\n";
  cout << "2 is the top right corner,\n";
  cout << "3 is the bottom left corner,\n";
  cout << "4 is the bottom right corner.\n";
  cin >> a >> b >> c >> d;
  for (int i = 0; i < 128; i++)
  {
    for (int j = 0; j < 128; j++)
    {
      if (a == 1)
        image1[i][j] = image[i][j];
      else if (a == 2)
        image1[i][j + 128] = image[i][j];
      else if (a == 3)
        image1[i + 128][j] = image[i][j];
      else
        image1[i + 128][j + 128] = image[i][j];
    }
  }
  for (int i = 0; i < 128; i++)
  {
    for (int j = 128; j < 256; j++)
    {
      if (b == 1)
        image2[i][j - 128] = image[i][j];
      else if (b == 2)
        image2[i][j] = image[i][j];
      else if (b == 3)
        image2[i + 128][j - 128] = image[i][j];
      else
        image2[i + 128][j] = image[i][j];
    }
  }
  for (int i = 128; i < 256; i++)
  {
    for (int j = 0; j < 128; j++)
      if (c == 1)
        image3[i - 128][j] = image[i][j];
      else if (c == 2)
        image3[i - 128][j + 128] = image[i][j];
      else if (c == 3)
        image3[i][j] = image[i][j];
      else
        image3[i][j + 128] = image[i][j];
  }
  for (int i = 128; i < 256; i++)
  {
    for (int j = 128; j < 256; j++)
    {
      if (d == 1)
        image4[i - 128][j - 128] = image[i][j];
      else if (d == 2)
        image4[i - 128][j] = image[i][j];
      else if (d == 3)
        image4[i][j - 128] = image[i][j];
      else
        image4[i][j] = image[i][j];
    }
  }
  for (int i = 0; i < 256; i++)
    for (int j = 0; j < 256; j++)
      image[i][j] = image1[i][j] + image2[i][j] + image3[i][j] + image4[i][j];
  saveImage();
}
// Blur
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
// Crop Image
void Crop()
{
  unsigned char new_image[SIZE][SIZE];
  int x, y, length, width;
  cout << "Please enter crop details in the following order: \n";
  cout << "x(start row) - y(start column) - length(num of rows) - width(num of columns): \n";
  cin >> x >> y >> length >> width;
  if (x < 0 || y < 0 || x + length > 256 || y + width > 256)
  {
    cerr << "Cropping window is outside the bounds of the image.\n";
    return;
  }
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      new_image[i][j] = ((i < x || i >= x + length || j < y || j >= y + width) ? 255 : image[i][j]);

  char imageFileName[100];

  // Get gray scale image target file name
  cout << "Enter the target image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  writeGSBMP(imageFileName, new_image);
}
// skew
