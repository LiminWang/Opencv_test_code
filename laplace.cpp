#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

 using namespace cv;

 int main(int argc, char** argv)
 {
    Mat src, src_gray, dst_gray, dst, disp;

    src = imread(argv[1]);

    //用高斯滤波降噪
    Mat g_src;
    GaussianBlur(src, g_src, Size(3, 3), 0, 0);

    //获取灰度图像
    cvtColor(g_src, src_gray, COLOR_RGB2GRAY);

    //Laplacian变换
    Laplacian(src_gray, dst_gray, CV_8U, 9, 1, 0, BORDER_DEFAULT);

    dst = Scalar::all(0);
    src.copyTo(dst, dst_gray);

    //合并原图和结果图显示
    hconcat(src, dst, disp);

    namedWindow(argv[1], CV_WINDOW_AUTOSIZE | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    imshow(argv[1], disp);

    waitKey();
    return 0;
 }
