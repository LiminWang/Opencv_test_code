
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    char* source_window = "Source Image";
    char* equalized_window = "Equalized Image";
    Mat src, dst;

    src = imread( argv[1], 1 );

    if( !src.data ) {
        cout <<"Usage: " << argv[0] << " <path_to_image>" << endl;
        return -1;
    }

    cvtColor( src, src, CV_BGR2GRAY );
    equalizeHist( src, dst );

    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );

    imshow( source_window, src );
    imshow( equalized_window, dst );

    waitKey(0);

    return 0;
}

