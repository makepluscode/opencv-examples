#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

double cameraMatrixValue[] = {
    1419.673553625388, 0., 666.5701993152168,
    0., 1415.434417595669, 284.9011670630352,
    0., 0., 1.
};

double distCoeffsValue[] = {-0.3779621578852622, -0.2007498881012056, 0.004339110290547984, 0.008265047579380602, 0.3210188752313808};

Mat cameraMatrix(3, 3, CV_64FC1, cameraMatrixValue);
Mat distCoeffs(1, 5, CV_64FC1, distCoeffsValue);

int main()
{
    Mat frame1 = imread("./images/img.jpg");
    Mat frame2;

    Mat map1, map2;
    Size imageSize=Size(800,600);

    initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(), cameraMatrix, imageSize, CV_32FC1, map1, map2);

    remap(frame1, frame2, map1, map2, INTER_LINEAR);

    imshow("Original Image", frame1);
    imshow("Rectified Image", frame2);

    waitKey(0);
    return 0;
}
