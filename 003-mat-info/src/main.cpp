#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

string parse_type(int type)
{
    string str;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar channels = 1 + (type >> CV_CN_SHIFT);

    switch (depth)
    {
        case CV_8U:
            str = "8U"; break;
        case CV_8S:
            str = "8S"; break;
        case CV_16U:
            str = "16U"; break;
        case CV_16S:
            str = "16S"; break;
        case CV_32S:
            str = "32S"; break;
        case CV_32F:
            str = "32F"; break;
        case CV_64F:
            str = "64F"; break;
        default:
            str = "User"; break;
    }

    str += "C";
    str += channels + '0';

    return str;
}

int main()
{
    cout << "opencv version : " << CV_VERSION << endl;
    
    // read a sample image
    Mat img;
    img = imread("./img/img.jpg");

    if(!img.empty())
    {
        String str = parse_type(img.type());
        cout << "This mat is " << str << " " << img.rows << "x" << img.cols << endl;
    }
    else
    {
    	cout << "image not found " << endl;
    }

    return 0;
}
