#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

//#define MIPI_CAMERA

int main()
{
#ifdef MIPI_CAMERA
    const char* gst_l = "v4l2src device=/dev/video0 ! video/x-raw, format=(string)UYVY, width=(int)1280, height=(int)720 ! \
        nvvidconv ! video/x-raw(memory:NVMM), format=(string)I420 ! nvvidconv ! appsink";
    const char* gst_r = "v4l2src device=/dev/video1 ! video/x-raw, format=(string)UYVY, width=(int)1280, height=(int)720 ! \
        nvvidconv ! video/x-raw(memory:NVMM), format=(string)I420 ! nvvidconv ! appsink";
#else
    const char* gst_l = "videotestsrc pattern=ball ! video/x-raw,width=1920,height=1080 ! videorate ! video/x-raw, \
        framerate=5/1 ! appsink";
    const char* gst_r = "videotestsrc pattern=ball ! video/x-raw,width=1920,height=1080 ! videorate ! video/x-raw, \
        framerate=5/1 ! appsink";
#endif

    // cout << getBuildInformation() << endl; 
    setenv("GST_DEBUG", "*:3", 0); 

    VideoCapture cap1(gst_l);
    VideoCapture cap2(gst_r);

    if(!cap1.isOpened() || !cap2.isOpened())
    {
       cout << "Failed to open camera(s)" << endl;
       return -1;
    }

    namedWindow("Left", WindowFlags::WINDOW_AUTOSIZE);
    namedWindow("Right", WindowFlags::WINDOW_AUTOSIZE);

    Mat img1, img2;

    while(1)
    {
        if (!cap1.read(img1) || !cap2.read(img2))
        {
            cout<<"Failed to read error"<<endl;
            break;
        }
        else
        {
            imshow("Left", img1);
            imshow("Right", img2);

            char key = waitKey(1);

            if(key == 27)
            {
                cout << "Exit" << endl;
                break;
            }
            if(key == 13)
            {
                static int num = 0;
                vector<int> params_jpg, params_png;
                params_jpg.push_back(IMWRITE_JPEG_QUALITY);          //JPG로 화질 설정
                params_jpg.push_back(95);
                imwrite("./images/left"  + std::to_string(num) + ".jpg", img1, params_jpg);
                imwrite("./images/right" + std::to_string(num) + ".jpg", img2, params_jpg);
                num++;
            }
        }
    }

    cap1.release();
    cap2.release();    

    return 0;
}
