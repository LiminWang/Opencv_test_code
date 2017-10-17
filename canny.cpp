#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    Mat src;
    Mat out;
    Mat dst, edge, gray;
    Mat disp;

    src = imread(argv[1]);

    //将原图像转为灰度
    cvtColor(src, gray, COLOR_RGB2GRAY);

    //滤波(降噪)
    blur(gray, edge, Size(3, 3));

    Canny(edge, out, 15, 10);

    dst = Scalar::all(0);
    src.copyTo(dst, out);

    //合并原图和结果图显示
    hconcat(src, dst, disp);

    namedWindow(argv[1], CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    imshow(argv[1], disp);

    waitKey();
    return 0;
}

