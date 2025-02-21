/**
 *  @file stats.cpp
 *  @description implementation of a stats class for rapid calculation of color averages
 *   and total color differences in CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "stats.h"

 /**
  *  Computes/retrieves the sum of a single color channel in a defined rectangular region
  *  @pre channel is a valid channel identifier
  *  @pre upper, left, lower, and right are valid image coordinates
  *  @param channel - one of 'r', 'g', or 'b'
  *  @param upper - y-coordinate of the upper edge of the rectangular region
  *  @param left - x-coordinate of the left side of the rectangular region
  *  @param lower - y-coordinate of the lower edge of the rectangular region
  *  @param right - x-coordinate of the right side of the rectangular region
  *  @return the sum of the appropriate color channel values in the defined rectangular area
  */
unsigned long Stats::GetColorSum(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned long sum = 0;
  if(upper == 0 && left == 0) {
    if (channel == 'r') {
      sum = sumR[lower][right];
    } else if (channel == 'g') {
      sum = sumG[lower][right];
    } else if (channel == 'b') {
      sum = sumB[lower][right];
    }
  } else if (upper == 0 && left >= 1) {
    if (channel == 'r') {
      sum = sumR[lower][right] - sumR[lower][left-1];
    } else if (channel == 'g') {
      sum = sumG[lower][right] - sumG[lower][left-1];
    } else if (channel == 'b') {
      sum = sumB[lower][right] - sumB[lower][left-1];
    }
  } else if (left == 0 && upper >= 1) {
    if (channel == 'r') {
      sum = sumR[lower][right] - sumR[upper-1][right];
    } else if (channel == 'g') {
      sum = sumG[lower][right] - sumG[upper-1][right];
    } else if (channel == 'b') {
      sum = sumB[lower][right] - sumB[upper-1][right];
    }
  } else {
    if (channel == 'r') {
      sum = sumR[lower][right] - sumR[upper-1][right] - sumR[lower][left-1] + sumR[upper-1][left -1];
    } else if (channel == 'g') {
      sum = sumG[lower][right] - sumG[upper-1][right] - sumG[lower][left-1] + sumG[upper-1][left -1];
    } else if (channel == 'b') {
      sum = sumB[lower][right] - sumB[upper-1][right] - sumB[lower][left-1] + sumB[upper-1][left -1];
    }
  }
	return sum; // REPLACE THIS STUB
}

/**
 *  Computes/retrieves the sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSum(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
	double sum = 0;
  if(upper == 0 && left == 0) {
    sum = sumA[lower][right];
  } else if (upper == 0 && left >= 1) {
    sum = sumA[lower][right] - sumA[lower][left-1];
  } else if (left == 0 && upper >= 1) {
    sum = sumA[lower][right] - sumA[upper-1][right];
  } else {
    sum = sumA[lower][right] - sumA[upper-1][right] - sumA[lower][left-1] + sumA[upper-1][left -1];
  }
	return sum;
}

/**
 *  Computes/retrieves the squared sum of a single color channel in a defined rectangular region
 *  @pre channel is a valid channel identifier
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param channel - one of 'r', 'g', or 'b'
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the appropriate color channel values in the defined rectangular area
 */
unsigned long Stats::GetColorSumSq(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
	unsigned long sum = 0;
  if(upper == 0 && left == 0) {
    if (channel == 'r') {
      sum = sumSqR[lower][right];
    } else if (channel == 'g') {
      sum = sumSqG[lower][right];
    } else if (channel == 'b') {
      sum = sumSqB[lower][right];
    }
  } else if (upper == 0 && left >= 1) {
    if (channel == 'r') {
      sum = sumSqR[lower][right] - sumSqR[lower][left-1];
    } else if (channel == 'g') {
      sum = sumSqG[lower][right] - sumSqG[lower][left-1];
    } else if (channel == 'b') {
      sum = sumSqB[lower][right] - sumSqB[lower][left-1];
    }
  } else if (left == 0 && upper >= 1) {
    if (channel == 'r') {
      sum = sumSqR[lower][right] - sumSqR[upper-1][right];
    } else if (channel == 'g') {
      sum = sumSqG[lower][right] - sumSqG[upper-1][right];
    } else if (channel == 'b') {
      sum = sumSqB[lower][right] - sumSqB[upper-1][right];
    }
  } else {
    if (channel == 'r') {
      sum = sumSqR[lower][right] - sumSqR[upper-1][right] - sumSqR[lower][left-1] + sumSqR[upper-1][left -1];
    } else if (channel == 'g') {
      sum = sumSqG[lower][right] - sumSqG[upper-1][right] - sumSqG[lower][left-1] + sumSqG[upper-1][left -1];
    } else if (channel == 'b') {
      sum = sumSqB[lower][right] - sumSqB[upper-1][right] - sumSqB[lower][left-1] + sumSqB[upper-1][left -1];
    }
  }
	return sum; 
}
/**
 *  Computes/retrieves the squared sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSumSq(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
	double sum = 0;
  if(upper == 0 && left == 0) {
    sum = sumSqA[lower][right];
  } else if (upper == 0 && left >= 1) {
    sum = sumSqA[lower][right] - sumSqA[lower][left-1];
  } else if (left == 0 && upper >= 1) {
    sum = sumSqA[lower][right] - sumSqA[upper-1][right];
  } else {
    sum = sumSqA[lower][right] - sumSqA[upper-1][right] - sumSqA[lower][left-1] + sumSqA[upper-1][left -1];
  }
	return sum;
}

/**
 *  Simple function to compute the number of pixels in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the area of the defined rectangular area, in pixels
 */
unsigned int Stats::GetRectangleArea(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  
	return (lower - upper + 1) * (right - left + 1); // REPLACE THIS STUB
}

/**
 *  Parameterized constructor
 *  Builds the channel sum and squared sum vectors from the supplied input image.
 *  Each channel sum vector's entry (x,y) will contain the sum of their respective
 *  color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *  Likewise, each channel squared sum vector's entry (x,y) will contain the squared sum of their
 *  respective color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *
 *  ***DON'T FORGET TO PRE-MULTIPLY THE ALPHA CHANNEL***
 * 
 *  @param img - input image from which the channel sum vectors will be populated
 */
Stats::Stats(const PNG& img) {
	// complete your implementation below
  sumR.resize(img.height());
  sumG.resize(img.height());
  sumB.resize(img.height());
  sumA.resize(img.height());

  sumSqR.resize(img.height());
  sumSqG.resize(img.height());
  sumSqB.resize(img.height());
  sumSqA.resize(img.height());
  for (unsigned int y = 0; y < img.height(); y++) {
    sumR[y].resize(img.width());
    sumG[y].resize(img.width());
    sumB[y].resize(img.width());
    sumA[y].resize(img.width());

    sumSqR[y].resize(img.width());
    sumSqG[y].resize(img.width());
    sumSqB[y].resize(img.width());
    sumSqA[y].resize(img.width());

    for (unsigned int x = 0; x < img.width(); x++) {

      RGBAPixel * pixel = img.getPixel(x, y);

      if (x == 0 && y == 0) {

        sumR[y][x] = pixel->r;
        sumG[y][x] = pixel->g;
        sumB[y][x] = pixel->b;
        sumA[y][x] = pixel->a * 255;

        sumSqR[y][x] = pixel->r * pixel->r;
        sumSqG[y][x] = pixel->g * pixel->g;
        sumSqB[y][x] = pixel->b * pixel->b;
        sumSqA[y][x] = pixel->a * pixel->a * 255;
        
      } else if (x == 0 && y >= 1) {

        sumR[y][x] = pixel->r + sumR[y-1][x];
        sumG[y][x] = pixel->g + sumG[y-1][x];
        sumB[y][x] = pixel->b + sumB[y-1][x];
        sumA[y][x] = pixel->a * 255 + sumA[y-1][x];

        sumSqR[y][x] = pixel->r * pixel->r + sumSqR[y-1][x];
        sumSqG[y][x] = pixel->g * pixel->g + sumSqG[y-1][x];
        sumSqB[y][x] = pixel->b * pixel->b + sumSqB[y-1][x];
        sumSqA[y][x] = pixel->a * pixel->a * 255 + sumSqA[y-1][x];

      } else if(y == 0 && x >= 1) {

        sumR[y][x] = pixel->r + sumR[y][x-1];
        sumG[y][x] = pixel->g + sumG[y][x-1];
        sumB[y][x] = pixel->b + sumB[y][x-1];
        sumA[y][x] = pixel->a + sumA[y][x-1];

        sumSqR[y][x] = pixel->r * pixel->r + sumSqR[y][x-1];
        sumSqG[y][x] = pixel->g * pixel->g + sumSqG[y][x-1];
        sumSqB[y][x] = pixel->b * pixel->b + sumSqB[y][x-1];
        sumSqA[y][x] = pixel->a * pixel->a * 255 + sumSqA[y][x-1];

      } else if (x >= 1 && y >= 1) {

        sumR[y][x] = pixel->r + sumR[y][x-1] + sumR[y-1][x] - sumR[y-1][x-1];
        sumG[y][x] = pixel->g + sumG[y][x-1] + sumG[y-1][x] - sumG[y-1][x-1];
        sumB[y][x] = pixel->b + sumB[y][x-1] + sumB[y-1][x] - sumB[y-1][x-1];
        sumA[y][x] = pixel->a + sumA[y][x-1] + sumA[y-1][x] - sumA[y-1][x-1];

        sumSqR[y][x] = pixel->r * pixel->r + sumSqR[y][x-1] + sumSqR[y-1][x] - sumSqR[y-1][x-1];
        sumSqG[y][x] = pixel->g * pixel->g + sumSqG[y][x-1] + sumSqG[y-1][x] - sumSqG[y-1][x-1];
        sumSqB[y][x] = pixel->b * pixel->b + sumSqB[y][x-1] + sumSqB[y-1][x] - sumSqB[y-1][x-1];
        sumSqA[y][x] = pixel->a * pixel->a * 255 + sumSqA[y][x-1] + sumSqA[y-1][x] - sumSqA[y-1][x-1];
      }
      
    }
  }
}

/**
 *  Computes/retrieves the average color of all pixels contained in the rectangle
 *  bounded by upper, left, lower, and right. Fractional values should be
 *  truncated/rounded down for assignment into integer variables.
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return pixel containing the average color of the pixels in the defined rectangle
 */
RGBAPixel Stats::GetAvg(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned int area = GetRectangleArea(upper, left, lower, right);
  unsigned int Ar = GetColorSum('r', upper, left, lower, right)/area;
  unsigned int Ag = GetColorSum('g', upper, left, lower, right)/area;
  unsigned int Ab = GetColorSum('b', upper, left, lower, right)/area;
  
  RGBAPixel average(Ar, Ag, Ab);
	return average; // REPLACE THIS STUB
}

/**
 *  Computes the total sum squared difference from the mean, for the specified rectangle.
 *  Each channel's sum squared difference is computed separately, and then added to form the total.
 *
 *  Note that using the GetAvg function in computing the sum squared difference will result in
 *  accumulation of error especially with larger rectangles.
 *  You should use more precise computation of the average color for this function's intermediate steps.
 * 
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return total sum of squared deviations from the mean, over all color channels.
 */
double Stats::GetSumSqDev(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  double rr = GetColorSumSq('r', upper, left, lower, right) 
  - (double) GetColorSum('r', upper, left, lower, right)* (double) GetColorSum('r', upper, left, lower, right)/(double)GetRectangleArea(upper,left,lower, right);

  double gg = GetColorSumSq('g', upper, left, lower, right) 
  - (double) GetColorSum('g', upper, left, lower, right)* (double) GetColorSum('g', upper, left, lower, right)/ (double) GetRectangleArea(upper,left,lower, right);

  double bb = GetColorSumSq('b', upper, left, lower, right) 
  - (double) GetColorSum('b', upper, left, lower, right)* (double) GetColorSum('b', upper, left, lower, right)/ (double) GetRectangleArea(upper,left,lower, right);


	return (double) rr + gg + bb; // REPLACE THIS STUB
}