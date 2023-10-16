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
void Edge();
void Enlarge();
void Shrink();
void mirrorImage();
void ShuffleImage();
void Blur();
void cropImage();

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
    cout << "d-cropImage\n";
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
            mirrorImage();

        else if (ch == 'b')
            ShuffleImage();

        else if (ch == 'c')
            Blur();
        else if (ch == 'd')
            cropImage();
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
    int avg = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            avg += image[i][j]; // calculating the average gray level
        }
    }
    avg = avg / (SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            bool higher = false, lower = false;
            if (image[i][j] >= avg)
            {
                higher = true; // check if the current pixel level is higher than the average
            }
            else
            {
                lower = true; // check if the current pixel level is lower than the average
            }
            if (higher)
            {
                if (image[i + 1][j] < avg || image[i][j + 1] < avg)
                {
                    image[i][j] = 0; // if the pixel is higher than the average and neighbour pixels is lower make it black (edge)
                }
                else
                {
                    image[i][j] = 255; // if the pixel is higher than the average and neighbour pixels isn't lower make it white
                }
            }
            else
            {
                if (image[i + 1][j] >= avg || image[i][j + 1] >= avg)
                {
                    image[i][j] = 0; // if the pixel is lower than the average and neighbour pixel is higher make it black (edge)
                }
                else
                {
                    image[i][j] = 255; // if the pixel is lower than the average and neighbour pixel is lower make it white
                }
            }
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

// Mirorr
void mirrorImage()
{
    // Function to mirror the loaded image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE / 2; j++)
        {
            // Swap pixels from left and right sides of the image
            unsigned char temp = image[i][j];
            image[i][j] = image[i][SIZE - 1 - j];
            image[i][SIZE - 1 - j] = temp;
        }
    }

    saveImage();
}
// ShuffleImage
void ShuffleImage()
{
    int totalPixels = SIZE * SIZE;
    unsigned char temp[totalPixels];

    // Copy all the pixels into a temporary array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            temp[i * SIZE + j] = image[i][j];
        }
    }

    // Shuffle the temporary array using the Fisher-Yates shuffle algorithm
    for (int i = totalPixels - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        // Swap pixels at indices i and j
        unsigned char pixel = temp[i];
        temp[i] = temp[j];
        temp[j] = pixel;
    }

    // Copy the shuffled pixels back to the image array
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = temp[i * SIZE + j];
        }
    }
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
// crop
void cropImage()
{
    int startX, startY, width, height;

    // Get crop coordinates and dimensions from the user
    cout << "Enter the starting X-coordinate for cropping: ";
    cin >> startX;
    cout << "Enter the starting Y-coordinate for cropping: ";
    cin >> startY;
    cout << "Enter the width for cropping: ";
    cin >> width;
    cout << "Enter the height for cropping: ";
    cin >> height;

    if (startX >= 0 && startY >= 0 && startX + width <= SIZE && startY + height <= SIZE)
    {
        // Create a new image for the cropped portion
        unsigned char croppedImage[SIZE][SIZE];
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                croppedImage[i][j] = image[startY + i][startX + j];
            }
        }

        // Save the cropped image with a new file name
        char outputFileName[100];
        cout << "Enter the target image file name for the cropped image: ";
        cin >> outputFileName;
        strcat(outputFileName, ".bmp");
        saveImage();
    }
    else
    {
        cout << "Invalid crop coordinates or dimensions. Make sure they are within the image boundaries." << endl;
    }
}
