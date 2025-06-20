
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int col = 0; col < height; col++) {
        for (int row = 0; row < width; row++) {
            int blue = image[col][row].rgbtBlue;
            int red = image[col][row].rgbtRed;
            int green = image[col][row].rgbtGreen;
            int avg = (blue + green + red) / 3;

            image[col][row].rgbtBlue = avg;
            image[col][row].rgbtGreen = avg;
            image[col][row].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int col = 0; col < height; col++) {
        if (width % 2 == 0) {
            int rev = width + 1;
            for (int row = 0, n = width / 2; row < n; row++) {
                RGBTRIPLE temp = image[col][row];
                image[col][row] = image[col][rev - 1];
                image[col][rev - 1] = temp;
                rev--;
            }
        } else {
            int rev = width + 1;
            for (int row = 0, n = (width - 1) / 2; row < n; row++) {
                RGBTRIPLE temp = image[col][row];
                image[col][row] = image[col][rev - 1];
                image[col][rev - 1] = temp;
                rev--;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    // Apply box blur directly on the image (in-place)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Iterate over neighboring pixels and self
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int ni = i + k;
                    int nj = j + l;

                    // Check bounds and accumulate from current image state
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute average and update pixel
            image[i][j].rgbtRed = (int)round((float)sumRed / count);
            image[i][j].rgbtGreen = (int)round((float)sumGreen / count);
            image[i][j].rgbtBlue = (int)round((float)sumBlue / count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) { return; }
