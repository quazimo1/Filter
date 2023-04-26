#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float x;
            x = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0;
            x = round(x);
            image[i][j].rgbtRed = (int)x;
            image[i][j].rgbtGreen = (int)x;
            image[i][j].rgbtBlue = (int)x;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            int r, g, b;
            r = image[i][width - 1 - j].rgbtRed;
            g = image[i][width - 1 - j].rgbtGreen;
            b = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtRed = image[i][j].rgbtRed;
            image[i][width - 1 - j].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float r = 0;
            float g = 0;
            float b = 0;
            //for top row
            if(i == 0 )
            {
                //top left corner
                if(j == 0)
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i + 1][j + 1].rgbtRed)/4.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen)/4.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue)/4.0;
                }
                //top right corner
                else if(j == width - 1)
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i + 1][j - 1].rgbtRed)/4.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i + 1][j - 1].rgbtGreen)/4.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue)/4.0;
                }
                //top edge
                else
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i + 1][j + 1].rgbtRed + image_copy[i + 1][j - 1].rgbtRed)/6.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen + image_copy[i + 1][j - 1].rgbtGreen)/6.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue)/6.0;
                }
            }
            //for bottom row
            else if(i == height - 1)
            {
                //bottom left corner
                if(j == 0)
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i - 1][j + 1].rgbtRed)/4.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen)/4.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue)/4.0;
                }
                //bottom right corner
                else if(j == width - 1)
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i - 1][j - 1].rgbtRed)/4.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i - 1][j - 1].rgbtGreen)/4.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i - 1][j - 1].rgbtBlue)/4.0;
                }
                //bottom edge
                else
                {
                    r += (image_copy[i][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i - 1][j + 1].rgbtRed + image_copy[i - 1][j - 1].rgbtRed)/6.0;
                    g += (image_copy[i][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen + image_copy[i - 1][j - 1].rgbtGreen)/6.0;
                    b += (image_copy[i][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue + image_copy[i - 1][j - 1].rgbtBlue)/6.0;
                }
            }
            //leftmost egde
            else if(j == 0 && i != 0 && i != height - 1)
            {
                r += (image_copy[i][j].rgbtRed + image_copy[i- 1][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i][j + 1].rgbtRed + image_copy[i - 1][j + 1].rgbtRed + image_copy[i + 1][j + 1].rgbtRed)/6.0;
                g += (image_copy[i][j].rgbtGreen + image_copy[i- 1][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i][j + 1].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen+ image_copy[i + 1][j + 1].rgbtGreen)/6.0;
                b += (image_copy[i][j].rgbtBlue + image_copy[i- 1][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i][j + 1].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue)/6.0;
            }
            //rightmost edge
            else if(j == width - 1 && i != 0 && i != height - 1)
            {
                r += (image_copy[i][j].rgbtRed + image_copy[i- 1][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i- 1][j - 1].rgbtRed + image_copy[i + 1][j - 1].rgbtRed)/6.0;
                g += (image_copy[i][j].rgbtGreen + image_copy[i- 1][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i - 1][j - 1].rgbtGreen+ image_copy[i + 1][j - 1].rgbtGreen)/6.0;
                b += (image_copy[i][j].rgbtBlue + image_copy[i- 1][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i - 1][j - 1].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue)/6.0;
            }
            //inside square
            else
            {
               r += (image_copy[i][j].rgbtRed + image_copy[i - 1][j].rgbtRed + image_copy[i + 1][j].rgbtRed + image_copy[i][j - 1].rgbtRed + image_copy[i - 1][j - 1].rgbtRed + image_copy[i + 1][j - 1].rgbtRed +  image_copy[i][j + 1].rgbtRed + image_copy[i - 1][j + 1].rgbtRed + image_copy[i + 1][j + 1].rgbtRed)/9.0;
               g += (image_copy[i][j].rgbtGreen + image_copy[i - 1][j].rgbtGreen + image_copy[i + 1][j].rgbtGreen + image_copy[i][j - 1].rgbtGreen + image_copy[i - 1][j - 1].rgbtGreen + image_copy[i + 1][j - 1].rgbtGreen +  image_copy[i][j + 1].rgbtGreen + image_copy[i - 1][j + 1].rgbtGreen + image_copy[i + 1][j + 1].rgbtGreen)/9.0;
               b += (image_copy[i][j].rgbtBlue + image_copy[i - 1][j].rgbtBlue + image_copy[i + 1][j].rgbtBlue + image_copy[i][j - 1].rgbtBlue + image_copy[i - 1][j - 1].rgbtBlue + image_copy[i + 1][j - 1].rgbtBlue +  image_copy[i][j + 1].rgbtBlue + image_copy[i - 1][j + 1].rgbtBlue + image_copy[i + 1][j + 1].rgbtBlue)/9.0;
            }
            image[i][j].rgbtRed = (int)round(r);
            image[i][j].rgbtGreen = (int)round(g);
            image[i][j].rgbtBlue = (int)round(b);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE image_copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }


    int x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int y[3][3] = {{-1, -2 , -1}, {0, 0, 0}, {1, 2, 1}};
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float r = 0;
            float g = 0;
            float b = 0;

            typedef struct
            {
                int r;
                int g;
                int b;
            }
            valuesof_x_y;

            valuesof_x_y a, c;

            a.r = 0;
            a.g = 0;
            a.b = 0;

            c.r = 0;
            c.g = 0;
            c.b = 0;

            //for top row
            if(i == 0 )
            {
                //top left corner
                if(j == 0)
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i + 1][j + 1].rgbtRed * x[2][2]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i + 1][j + 1].rgbtGreen * x[2][2]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i + 1][j + 1].rgbtBlue * x[2][2]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i + 1][j + 1].rgbtRed * y[2][2]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i + 1][j + 1].rgbtGreen * y[2][2]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i + 1][j + 1].rgbtBlue * y[2][2]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
                //top right corner
                else if(j == width - 1)
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i + 1][j - 1].rgbtRed * x[2][0]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i + 1][j - 1].rgbtGreen * x[2][0]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i + 1][j + 1].rgbtBlue * x[2][0]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i + 1][j - 1].rgbtRed * y[2][0]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i + 1][j - 1].rgbtGreen * y[2][0]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i + 1][j - 1].rgbtBlue * y[2][0]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
                //top edge
                else
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i + 1][j + 1].rgbtRed * x[2][2] + image_copy[i + 1][j - 1].rgbtRed * x[2][0]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i + 1][j + 1].rgbtGreen * x[2][2] + image_copy[i + 1][j - 1].rgbtGreen * x[2][0]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i + 1][j + 1].rgbtBlue * x[2][2] + image_copy[i + 1][j - 1].rgbtBlue * x[2][0]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i + 1][j + 1].rgbtRed * y[2][2] + image_copy[i + 1][j - 1].rgbtRed * y[2][0]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i + 1][j + 1].rgbtGreen * y[2][2] + image_copy[i + 1][j - 1].rgbtGreen * y[2][0]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i + 1][j + 1].rgbtBlue * y[2][2] + image_copy[i + 1][j - 1].rgbtBlue * y[2][0]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
            }
            //for bottom row
            else if(i == height - 1)
            {
                //bottom left corner
                if(j == 0)
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i - 1][j].rgbtRed * x[0][1] + image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i - 1][j + 1].rgbtRed * x[0][2]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i - 1][j].rgbtGreen * x[0][1] + image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i - 1][j + 1].rgbtGreen * x[0][2]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i - 1][j].rgbtBlue * x[0][1] + image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i - 1][j + 1].rgbtBlue * x[0][2]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i - 1][j].rgbtRed * y[0][1] + image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i - 1][j + 1].rgbtRed * y[0][2]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i - 1][j].rgbtGreen * y[0][1] + image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i - 1][j + 1].rgbtGreen * y[0][2]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i - 1][j].rgbtBlue * y[0][1] + image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i - 1][j + 1].rgbtBlue * y[0][2]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
                //bottom right corner
                else if(j == width - 1)
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i - 1][j].rgbtRed * x[0][1] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i - 1][j - 1].rgbtRed * x[0][0]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i - 1][j].rgbtGreen * x[0][1] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i - 1][j - 1].rgbtGreen * x[0][0]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i - 1][j].rgbtBlue * x[0][1] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i - 1][j - 1].rgbtBlue * x[0][0]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i - 1][j].rgbtRed * y[0][1] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i - 1][j - 1].rgbtRed * y[0][0]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i - 1][j].rgbtGreen * y[0][1] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i - 1][j - 1].rgbtGreen * y[0][0]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i - 1][j].rgbtBlue * y[0][1] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i - 1][j - 1].rgbtBlue * y[0][0]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
                //bottom edge
                else
                {
                    a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i - 1][j].rgbtRed * x[0][1] + image_copy[i - 1][j + 1].rgbtRed * x[0][2] + image_copy[i - 1][j - 1].rgbtRed * x[0][0]);
                    a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i - 1][j].rgbtGreen * x[0][1] + image_copy[i - 1][j + 1].rgbtGreen * x[0][2] + image_copy[i - 1][j - 1].rgbtGreen * x[0][0]);
                    a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i - 1][j].rgbtBlue * x[0][1] + image_copy[i - 1][j + 1].rgbtBlue * x[0][2] + image_copy[i - 1][j - 1].rgbtBlue * x[0][0]);

                    c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i - 1][j].rgbtRed * y[0][1] + image_copy[i - 1][j + 1].rgbtRed * y[0][2] + image_copy[i - 1][j - 1].rgbtRed * y[0][0]);
                    c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i - 1][j].rgbtGreen * y[0][1] + image_copy[i - 1][j + 1].rgbtGreen * y[0][2] + image_copy[i - 1][j - 1].rgbtGreen * y[0][0]);
                    c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i - 1][j].rgbtBlue * y[0][1] + image_copy[i - 1][j + 1].rgbtBlue * y[0][2] + image_copy[i - 1][j - 1].rgbtBlue * y[0][0]);

                    r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                    g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                    b += ((sqrt((a.b * a.b) + (c.b * c.b))));
                }
            }
            //leftmost egde
            else if(j == 0 && i != 0 && i != height - 1)
            {

                a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i- 1][j].rgbtRed * x[0][1] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i - 1][j + 1].rgbtRed * x[0][2] + image_copy[i + 1][j + 1].rgbtRed * x[2][2]);
                a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i- 1][j].rgbtGreen * x[0][1] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i - 1][j + 1].rgbtGreen * x[0][2] + image_copy[i + 1][j + 1].rgbtGreen * x[2][2]);
                a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i- 1][j].rgbtBlue * x[0][1] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i - 1][j + 1].rgbtBlue * x[0][2] + image_copy[i + 1][j + 1].rgbtBlue * x[2][2]);

                c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i- 1][j].rgbtRed * y[0][1] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i - 1][j + 1].rgbtRed * y[0][2] + image_copy[i + 1][j + 1].rgbtRed * y[2][2]);
                c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i- 1][j].rgbtGreen * y[0][1] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i - 1][j + 1].rgbtGreen * y[0][2] + image_copy[i + 1][j + 1].rgbtGreen * y[2][2]);
                c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i- 1][j].rgbtBlue * y[0][1] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i - 1][j + 1].rgbtBlue * y[0][2] + image_copy[i + 1][j + 1].rgbtBlue * y[2][2]);

                r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                b += ((sqrt((a.b * a.b) + (c.b * c.b))));
            }
            //rightmost edge
            else if(j == width - 1 && i != 0 && i != height - 1)
            {

                a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i - 1][j].rgbtRed * x[0][1] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i- 1][j - 1].rgbtRed * x[0][0] + image_copy[i + 1][j - 1].rgbtRed * x[2][0]);
                a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i - 1][j].rgbtGreen * x[0][1] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i - 1][j - 1].rgbtGreen * x[0][0]+ image_copy[i + 1][j - 1].rgbtGreen * x[2][0]);
                a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i - 1][j].rgbtBlue * x[0][1] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i - 1][j - 1].rgbtBlue * x[0][0] + image_copy[i + 1][j - 1].rgbtBlue * x[2][0]);

                c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i - 1][j].rgbtRed * y[0][1] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i- 1][j - 1].rgbtRed * y[0][0] + image_copy[i + 1][j - 1].rgbtRed * y[2][0]);
                c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i - 1][j].rgbtGreen * y[0][1] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i - 1][j - 1].rgbtGreen * y[0][0]+ image_copy[i + 1][j - 1].rgbtGreen * y[2][0]);
                c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i - 1][j].rgbtBlue * y[0][1] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i - 1][j - 1].rgbtBlue * y[0][0] + image_copy[i + 1][j - 1].rgbtBlue * y[2][0]);

                r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                b += ((sqrt((a.b * a.b) + (c.b * c.b))));
            }
            //inside square
            else
            {
               a.r += (image_copy[i][j].rgbtRed * x[1][1] + image_copy[i - 1][j].rgbtRed * x[0][1] + image_copy[i + 1][j].rgbtRed * x[2][1] + image_copy[i][j - 1].rgbtRed * x[1][0] + image_copy[i - 1][j - 1].rgbtRed * x[0][0] + image_copy[i + 1][j - 1].rgbtRed * x[2][0] +  image_copy[i][j + 1].rgbtRed * x[1][2] + image_copy[i - 1][j + 1].rgbtRed * x[0][2] + image_copy[i + 1][j + 1].rgbtRed * x[2][2]);
               a.g += (image_copy[i][j].rgbtGreen * x[1][1] + image_copy[i - 1][j].rgbtGreen * x[0][1] + image_copy[i + 1][j].rgbtGreen * x[2][1] + image_copy[i][j - 1].rgbtGreen * x[1][0] + image_copy[i - 1][j - 1].rgbtGreen * x[0][0] + image_copy[i + 1][j - 1].rgbtGreen * x[2][0] +  image_copy[i][j + 1].rgbtGreen * x[1][2] + image_copy[i - 1][j + 1].rgbtGreen * x[0][2] + image_copy[i + 1][j + 1].rgbtGreen * x[2][2]);
               a.b += (image_copy[i][j].rgbtBlue * x[1][1] + image_copy[i - 1][j].rgbtBlue * x[0][1] + image_copy[i + 1][j].rgbtBlue * x[2][1] + image_copy[i][j - 1].rgbtBlue * x[1][0] + image_copy[i - 1][j - 1].rgbtBlue * x[0][0] + image_copy[i + 1][j - 1].rgbtBlue * x[2][0] +  image_copy[i][j + 1].rgbtBlue * x[1][2] + image_copy[i - 1][j + 1].rgbtBlue * x[0][2] + image_copy[i + 1][j + 1].rgbtBlue * x[2][2]);

               c.r += (image_copy[i][j].rgbtRed * y[1][1] + image_copy[i - 1][j].rgbtRed * y[0][1] + image_copy[i + 1][j].rgbtRed * y[2][1] + image_copy[i][j - 1].rgbtRed * y[1][0] + image_copy[i - 1][j - 1].rgbtRed * y[0][0] + image_copy[i + 1][j - 1].rgbtRed * y[2][0] +  image_copy[i][j + 1].rgbtRed * y[1][2] + image_copy[i - 1][j + 1].rgbtRed * y[0][2] + image_copy[i + 1][j + 1].rgbtRed * y[2][2]);
               c.g += (image_copy[i][j].rgbtGreen * y[1][1] + image_copy[i - 1][j].rgbtGreen * y[0][1] + image_copy[i + 1][j].rgbtGreen * y[2][1] + image_copy[i][j - 1].rgbtGreen * y[1][0] + image_copy[i - 1][j - 1].rgbtGreen * y[0][0] + image_copy[i + 1][j - 1].rgbtGreen * y[2][0] +  image_copy[i][j + 1].rgbtGreen * y[1][2] + image_copy[i - 1][j + 1].rgbtGreen * y[0][2] + image_copy[i + 1][j + 1].rgbtGreen * y[2][2]);
               c.b += (image_copy[i][j].rgbtBlue * y[1][1] + image_copy[i - 1][j].rgbtBlue * y[0][1] + image_copy[i + 1][j].rgbtBlue * y[2][1] + image_copy[i][j - 1].rgbtBlue * y[1][0] + image_copy[i - 1][j - 1].rgbtBlue * y[0][0] + image_copy[i + 1][j - 1].rgbtBlue * y[2][0] +  image_copy[i][j + 1].rgbtBlue * y[1][2] + image_copy[i - 1][j + 1].rgbtBlue * y[0][2] + image_copy[i + 1][j + 1].rgbtBlue * y[2][2]);

                r += ((sqrt((a.r * a.r) + (c.r * c.r))));
                g += ((sqrt((a.g * a.g) + (c.g * c.g))));
                b += ((sqrt((a.b * a.b) + (c.b * c.b))));
            }
            if((int)round(r) > 255)
            {
                r = 255;
            }

            if((int)round(g) > 255)
            {
                g = 255;
            }

            if((int)round(b) > 255)
            {
                b = 255;
            }

            image[i][j].rgbtRed = (int)round(r);
            image[i][j].rgbtGreen = (int)round(g);
            image[i][j].rgbtBlue = (int)round(b);
        }
    }
    return;
}
