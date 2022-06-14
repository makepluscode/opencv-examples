#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

//#define CUSTOM_IMAGE
//#define SGBM

int main()
{
    cout << "opencv version : " << CV_VERSION << endl;

    // read 2 images (as 8UC1)
    Mat imgl, imgr;
    Mat img1, img2;

#ifdef CUSTOM_IMAGE
    imgl = imread("./img/left14_cal.jpg", IMREAD_GRAYSCALE );
    imgr = imread("./img/right14_cal.jpg", IMREAD_GRAYSCALE );

    resize(imgl, img1, Size(960,540));
    resize(imgr, img2, Size(960,540));
#else
    img1 = imread("./img/tsukuba_l.png", IMREAD_GRAYSCALE );
    img2 = imread("./img/tsukuba_r.png", IMREAD_GRAYSCALE );
#endif

    // stereo image
    Mat img_disparity_16s, img_disparity_8u;

#ifdef SGBM
    int min_disparities = 0;
    int num_disparities = 16;
    int blocksize = 15;

    cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(min_disparities, num_disparities, blocksize);
    sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
    sgbm->compute(img1, img2, img_disparity_16s);
#else
    int num_disparities = 16;
    int blocksize = 15;

    cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create(num_disparities, blocksize);
    stereo->compute(img1, img2, img_disparity_16s);
#endif


#ifndef NORMALIZE_MANUAL
    // normalize img_disparity_16s manually
    double minVal; double maxVal;
    minMaxLoc( img_disparity_16s, &minVal, &maxVal );
    cout << "min : " << minVal << ", max : " << maxVal << endl;
    img_disparity_16s.convertTo(img_disparity_8u, CV_8UC1, 255/(maxVal - minVal));
#else
    normalize(img_disparity_16s, img_disparity_8u, 0, 255, CV_MINMAX, CV_8U);
#endif
    // normalize img_disparity_16s with opencv api
    imshow("left", img1);
    imshow("right", img2);    
    imshow("disparity", img_disparity_8u);

    waitKey(0);

    return 0;
}
