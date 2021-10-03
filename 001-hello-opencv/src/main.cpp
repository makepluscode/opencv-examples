#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "opencv version : " << CV_VERSION << endl;
    
    Mat img;
    img = imread("./img/google.png");
    
    if(!img.empty())
    {
        namedWindow("image");
        imshow("image", img);
        waitKey(0);
    }
    else
    {
    	cout << "imgae not found " << CV_VERSION << endl;
    }

    return 0;
}
