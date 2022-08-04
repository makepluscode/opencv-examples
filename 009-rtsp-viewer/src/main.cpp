#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat frame1, frame2;

    cv::VideoCapture source1("rtsp://192.168.1.6:8554/ds-test");
    cv::VideoCapture source2("rtsp://192.168.1.6:8555/ds-test");

    while (cv::waitKey(1) < 1)
    {
        source1 >> frame1;
        source2 >> frame2;
        if (frame1.empty() || frame2.empty() )
        {
            cv::waitKey();
            break;
        }

        cv::imshow("output1", frame1); 
        cv::imshow("output2", frame2); 
    }


    waitKey(0);
    return 0;
}
