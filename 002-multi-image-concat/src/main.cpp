#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "opencv version : " << CV_VERSION << endl;
    
    // read 2 images
    Mat imgl, imgr;
    imgl = imread("./img/capture0.jpg");
    imgr = imread("./img/capture1.jpg");

    // resize 2 images to small (540x270)
    Mat img1, img2;
    resize(imgl, img1, Size(540,270));
    resize(imgr, img2, Size(540,270));

    // create new 2 image more
    Mat img3, img4;
    img3 = img1 + img2;
	img4 = 0.5*img1 + 0.5*img2;

    if(!imgl.empty() || !imgr.empty())
    {
        Mat main;
        Mat h1, h2;

        hconcat(img1, img2, h1);
        hconcat(img3, img4, h2);
        vconcat(h1, h2, main);
        imshow("main", main);
        waitKey(0);
    }
    else
    {
    	cout << "image not found " << CV_VERSION << endl;
    }

    return 0;
}
