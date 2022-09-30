#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])   //struct encapsulating the bytes(3) 1 for each
{
    //
    int cal_average;
    for (int i = 0; i < height; i++)                          //iterating through each pixel, which is height and width
    {
        for (int j = 0; j < width; j++)
        {
            int Red = image[i][j].rgbtRed;
            int Green = image[i][j].rgbtGreen;
            int Blue = image[i][j].rgbtBlue;
            cal_average = round(((float)Red + (float)Green + (float)Blue) / 3); // calculating the average value pixel and rounding to single number
            image[i][j].rgbtRed = cal_average;
            image[i][j].rgbtGreen = cal_average;                            //setting each color equals to average
            image[i][j].rgbtBlue = cal_average;
        }
    }


}

// Convert image to sepia

//we r provided with formulas to calculate sepia of each color
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int original_Red, original_Green, original_Blue;
    int sepia_Red, sepia_Blue, sepia_Green;

    //iterate through the height
    for ( int i = 0; i < height; i++)            //iterating through each pixel
    {
        for (int j = 0; j < width; j++)
        {
            //assign each value to variable created
            original_Red = image[i][j].rgbtRed;
            original_Green = image[i][j].rgbtGreen;
            original_Blue = image[i][j].rgbtBlue;

             //values should be between 0-255
            //calculate for sepiaColor and assign new value

            sepia_Red = round(0.393 * original_Red + 0.769 * original_Green + 0.189 * original_Blue);


            if (sepia_Red > 255)           //if color is greater than 255 , setting new color 255
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepia_Red;      // else color remains same
            }

            //calculate for sepia_Green and assign new value
            sepia_Green = round(0.349 * original_Red + 0.686 * original_Green + 0.168 * original_Blue);
            if (sepia_Green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepia_Green;
            }
            //Calculate for sepia_Blue and assign new value
            sepia_Blue = round(0.272 * original_Red + 0.534 * original_Green + 0.131 * original_Blue);
            if (sepia_Blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepia_Blue;
            }
        }

    }

}

// Reflect image horizontally
//for reflecting we have to swap the pixels from left to right of an image,
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)              //iterating through the height but half width
    {
        for (int j = 0; j < (width/2); j++)
        {
            //storing the original image in temp variable
            int temp_Red = image[i][j].rgbtRed;
            int temp_green = image[i][j].rgbtGreen;
            int temp_blue = image[i][j].rgbtBlue;

            //storing the right half image in original one

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            //and then storing the temp in the right image
            image[i][width - j - 1].rgbtRed = temp_Red;
            image[i][width - j - 1].rgbtGreen = temp_green;
            image[i][width - j - 1].rgbtBlue = temp_blue;
        }


    }


}

// Blur image

//using boxblur which takes each pixel and for each color, giving it new value by averaging neighbour pixel
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //create a temporary image to implement blurred algorithm on it.
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_Red, total_Blue, total_Green;
            total_Red = total_Blue = total_Green = 0;
            float counter = 0.00;


            for (int x = -1; x < 2; x++)                      ////Geting the neighbouring pexels
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //checking if  neighbouring pexels are valid
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //getting image value
                    total_Red += image[currentX][currentY].rgbtRed;
                    total_Green += image[currentX][currentY].rgbtGreen;
                    total_Blue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }

                //calculating the average of neigbhouring pexels
                temp[i][j].rgbtRed = round(total_Red / counter);
                temp[i][j].rgbtGreen = round(total_Green / counter);
                temp[i][j].rgbtBlue = round(total_Blue / counter);
            }
        }

    }

    //copy the blurr image to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

}
