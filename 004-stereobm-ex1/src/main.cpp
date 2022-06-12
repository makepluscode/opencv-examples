#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "opencv version : " << CV_VERSION << endl;
    
    // read 2 images (as 8UC1)
    Mat imgl, imgr;
    imgl = imread("./img/capture0.jpg", IMREAD_GRAYSCALE );
    imgr = imread("./img/capture1.jpg", IMREAD_GRAYSCALE );

    // resize 2 images to small (540x270)
    Mat img1, img2;
    resize(imgl, img1, Size(960,540));
    resize(imgr, img2, Size(960,540));

    // StereoBM
    int ndisparities = 16;
    int blocksize = 21;

    // create stereo image
    Mat img_disparity_16s, img_disparity_8u;

    cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create(ndisparities, blocksize);
    stereo->compute(img1, img2, img_disparity_16s);

    // normalize img_disparity_16s
    double minVal; double maxVal;
    minMaxLoc( img_disparity_16s, &minVal, &maxVal );
    cout << "min : " << minVal << ", max : " << maxVal << endl;
    img_disparity_16s.convertTo(img_disparity_8u, CV_8UC1, 255/(maxVal - minVal));

    imshow("left", img1);
    imshow("right", img2);    
    imshow("disparity", img_disparity_8u);

    waitKey(0);

    return 0;
}
