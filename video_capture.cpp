#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    bool exit = false;
    int key;
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        return 1;
    }


    while (!exit) {
        Mat frame;

        if (!cap.read(frame)) {
            cout << "Could not get frame\n";
            break;
        }

        imshow("video capture", frame);

        int key = waitKey(5);
        /* ESC */
        if (key == 27) {
            exit = true;
        }
    }

    return 0;
}
