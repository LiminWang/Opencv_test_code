#include <opencv/cv.h>
#include <opencv/cxmisc.h>
#include <opencv/cxcore.h>
#include <opencv/ml.h>
#include <opencv/cvaux.h>
#include <opencv/cvwimage.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "copista.h"

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  /// Create Window
  namedWindow( "Source", WINDOW_NORMAL );
  imshow("Source", src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Convert image to gray and blur it
//  inRange(src,Scalar(0,0,0), Scalar(255,255,100),src_gray);

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  Mat F = src.clone();
  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       cout << inspect_countour(contours[i]) << "\n";
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours(F, contours, i, color, 2, 8, hierarchy, 0, Point() );
       Rect rect = minAreaRect(contours[i]).boundingRect();
       rectangle(F, rect.tl(), rect.br(), Scalar(255,0,0), 1, 8, 0 );
     }


  /// Show in a window
  namedWindow( "Contours", WINDOW_NORMAL );
  imshow( "Contours", F );
}
