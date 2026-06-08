#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for(int h=0; h<height; h++) {
    for(int w=0; w<width; w++) {
      int average = (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3;
      image[h][w].rgbtRed = average;
      image[h][w].rgbtGreen = average;
      image[h][w].rgbtBlue = average;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  int half_width = width/2 + width%2;
  for (int h=0; h<height; h++) {
    for(int w=0; w<half_width; w++) {
      if (w == width - 1 - w) {
        continue;
      }

      RGBTRIPLE temp;
      temp.rgbtRed = image[h][w].rgbtRed;
      temp.rgbtGreen = image[h][w].rgbtGreen;
      temp.rgbtBlue = image[h][w].rgbtBlue;

      image[h][w].rgbtRed = image[h][width - w].rgbtRed;
      image[h][w].rgbtGreen = image[h][width - w].rgbtGreen;
      image[h][w].rgbtBlue = image[h][width - w].rgbtBlue;

      image[h][width - w].rgbtRed = temp.rgbtRed;
      image[h][width - w].rgbtGreen = temp.rgbtGreen;
      image[h][width - w].rgbtBlue = temp.rgbtBlue;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
  int blur_size = 2;

  for (int h=0; h<height; h++) {
    for(int w=0; w<width; w++) {
      int total = 0;
      int total_red = 0;
      int total_green = 0;
      int total_blue = 0;

      for(int i=-blur_size; i<=blur_size; i++) {
        for(int j=-blur_size; j<=blur_size; j++) {
          if (
            h+i >= 0 && h+i < height &&
            w+j >= 0 && w+j < width
          ) {
            total++;
            total_red += image[h+i][w+j].rgbtRed;
            total_green += image[h+i][w+j].rgbtGreen;
            total_blue += image[h+i][w+j].rgbtBlue;
          }
        }
      }

      temp[h][w].rgbtRed = total_red / total;
      temp[h][w].rgbtGreen = total_green / total;
      temp[h][w].rgbtBlue = total_blue / total;
    }
  }

  for(int h=0; h<height; h++) {
    for(int w=0; w<width; w++) {
      image[h][w].rgbtRed = temp[h][w].rgbtRed;
      image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
      image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
    }
  }

  free(temp);
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
  int gx_kernel[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1},
  };

  int gy_kernel[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1},
  };

  RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

  for(int h=0; h<height; h++) {
    for(int w=0; w<width; w++) {
      int gx_red = 0;
      int gx_blue = 0;
      int gx_green = 0;

      int gy_red = 0;
      int gy_blue = 0;
      int gy_green = 0;

      for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
          if (
              h+i >=0 && h+i < height &&
              w+j >=0 && w+j < width
          ) {
            gx_red += gx_kernel[i+1][j+1] * image[h+i][w+j].rgbtRed;
            gx_green += gx_kernel[i+1][j+1] * image[h+i][w+j].rgbtGreen;
            gx_blue += gx_kernel[i+1][j+1] * image[h+i][w+j].rgbtBlue;

            gy_red += gy_kernel[i+1][j+1] * image[h+i][w+j].rgbtRed;
            gy_green += gy_kernel[i+1][j+1] * image[h+i][w+j].rgbtGreen;
            gy_blue += gy_kernel[i+1][j+1] * image[h+i][w+j].rgbtBlue;
          }
        }
      }

      temp[h][w].rgbtRed = fmin(rint(sqrt(gx_red*gx_red + gy_red*gy_red)), 255);
      temp[h][w].rgbtGreen = fmin(rint(sqrt(gx_green*gx_green + gy_green*gy_green)), 255);
      temp[h][w].rgbtBlue = fmin(rint(sqrt(gx_blue*gx_blue + gy_blue*gy_blue)), 255);
    }
  }

  for(int h=0; h<height; h++) {
    for(int w=0; w<width; w++) {
      image[h][w].rgbtRed = temp[h][w].rgbtRed;
      image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
      image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
    }
  }

  free(temp);
  return;
}
