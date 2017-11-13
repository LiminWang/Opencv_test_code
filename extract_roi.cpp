#include <iostream>
#include <string>
#include <stack>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


using namespace std;
using namespace cv;

bool ldown = false; // left mouse button down flag
bool lup = false; // left mouse button up flag

Mat img; // original image
Mat croppedImage; // cropped image
Point corner1, corner2; // Starting and ending of the user's selection point
Rect box; // (ROI)Regions of Interest

// Callback function for mouse events
static void mouse_callback(int event, int x, int y, int, void*)
{
    // when left mouse button is pressed
    if (event == EVENT_LBUTTONDOWN) {
        ldown = true;
        // record its position and save it in corner1
        corner1.x = x;
        corner1.y = y;
        cout << "Corner 1 recorded at " << corner1 << endl;
    }
    // when left mouse button is released
    if (event == EVENT_LBUTTONUP) {
        // if user selection is bigger than 20 piexels
        if (abs(x - corner1.x) > 20 && abs(y - corner1.y) > 20) {
            lup = true;
            // record its position and save it in corner1
            corner2.x = x;
            corner2.y = y;
            cout << "Corner 2 recorded at " << corner2 <<  endl << endl;
        }
        else
        {
            cout << "Please select a bigger region" << endl;
            ldown = false;
        }
    }
    // update the box showing the selected region as the user drags the mouse
    if (ldown == true && lup == false) {
        Point pt;
        pt.x = x;
        pt.y = y;
        Mat local_img = img.clone();
        rectangle(local_img, corner1, pt, Scalar(0, 0, 255)); // b, g, r
        imshow("Cropping app", local_img);
    }
    // Define ROI and crop it out when both corners have been selected
    if (ldown == true && lup == true) {
        box.width = abs(corner1.x - corner2.x); // 2 個 corner X 軸座標距離的絕對值
        box.height = abs(corner1.y - corner2.y); // 2 個 corner Y 軸座標距離的絕對值
        box.x = min(corner1.x, corner2.x); // 2 個 corner X 軸座標的最小值
        box.y = min(corner1.y, corner2.y); // 2 個 corner Y 軸座標的最小值
        
        // Make a image out of just the selected ROI and display it in a new window
        Mat crop(img, box);
        namedWindow("Crop");
        imshow("Crop", crop);
        
        // clone the cropped image(ROI) and save it to a file
        croppedImage = img(box).clone();
        imwrite("cropped.png", croppedImage);
        
        ldown = false;
        lup = false;
    }
}

int main(int argc, const char *argv[])
{
    // Read image
    img = imread(argv[1]);
    namedWindow("Cropping app");
    imshow("Cropping app", img);
    
    setMouseCallback("Cropping app", mouse_callback);
    
    while (char(waitKey(1) != 'q')) {
    }
    
    return 0;
}

