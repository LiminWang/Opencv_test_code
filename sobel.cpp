#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    Mat src;
    Mat out;
    Mat sobelx, sobely;
    Mat disp;

    src = imread(argv[1]);

    // Display image
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", src);

    // Apply sobel filter with only x gradient
    Sobel(src, sobelx, CV_32F, 1, 0);
    // Apply sobel filter with only y gradient 
    Sobel(src, sobely, CV_32F, 0, 1);

    //合并原图和结果图显示
    hconcat(sobelx, sobely, disp);

    namedWindow(argv[1], CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    imshow(argv[1], disp);

    waitKey();
    return 0;
}

