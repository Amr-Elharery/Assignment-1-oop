// FCAI – OOP Programming – 2023 - Assignment 1 Bonus
// Program Name:CS213-2023-6-20220160-20220018-20220237-A1Bonus.cpp
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

unsigned char RGBImage[SIZE][SIZE][RGB];

void loadRGB();
void saveRGB();
void showOptions();
void menu();
void bwFilter();
void Invert();
void Darken();
void Lighten();

int main()
{
    loadRGB();
    menu();
}

// Options
void showOptions()
{

    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1-	Black & White Filter\n";
    cout << "2-	Invert Filter\n";
    cout << "3-	Darken and Lighten Image\n";
    cout << "s- For save Image\n";
    cout << "0- For Exit\n";
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
            char mode;
            cout << "Do you want to (d)arken or (l)ighten ?\n";

            cin >> mode;

            if (mode == 'l')
                Lighten();
            if (mode == 'd')
                Darken();
        }

        else if (ch == 's')
            saveRGB();

        showOptions();
        cin >> ch;
    }
}

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

void bwFilter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                if (RGBImage[i][j][k] > 100)
                    RGBImage[i][j][k] = 255;
                else
                    RGBImage[i][j][k] = 0;
            }
        }
    }
    saveRGB();
}

void Invert()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = 255 - RGBImage[i][j][k];
            }
        }
    }
    saveRGB();
}

// Lighten

void Lighten()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                if (RGBImage[i][j][k] <= 190)
                    RGBImage[i][j][k] += 65;
            }
        }
    }
    saveRGB();
}

// Darken

void Darken()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                RGBImage[i][j][k] = RGBImage[i][j][k] / 2;
            }
        }
    }
    saveRGB();
}