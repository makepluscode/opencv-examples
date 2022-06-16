#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

const int CHECKERBOARD[2]{8,6};

// orignal codes
// https://learnopencv.com/camera-calibration-using-opencv/


int main()
{
    // creating vector to store vectors of 3D points
    vector<vector<Point3f> > objpoints;

    // creating vector to store vectors of 2D points
    vector<vector<Point2f> > imgpoints;

    // Defining the world coordinates for 3D points
    vector<Point3f> objp;
    for(int i{0}; i<CHECKERBOARD[1]; i++)
    {
        for(int j{0}; j<CHECKERBOARD[0]; j++)
        objp.push_back(Point3f(j,i,0));
    }

    vector<String> images;
    string path = "./images/*.jpg";

    glob(path, images);

    Mat frame, gray;
    // vector to store the pixel coordinates of detected checker board corners 
    vector<Point2f> corner_pts;
    bool success;

    // Looping over all the images in the directory
    for(int i{0}; i<images.size(); i++)
    {
        frame = imread(images[i]);
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Finding checker board corners
        // If desired number of corners are found in the image then success = true  
        success = findChessboardCorners(gray, Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts,
        CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

        /* 
        * If desired number of corner are detected,
        * we refine the pixel coordinates and display 
        * them on the images of checker board
        */
        if(success)
        {
            TermCriteria criteria(TermCriteria::EPS | TermCriteria::MAX_ITER, 30, 0.001);

            // refining pixel coordinates for given 2d points.
            cornerSubPix(gray,corner_pts,Size(11,11), Size(-1,-1), criteria);

            // Displaying the detected corner points on the checker board
            drawChessboardCorners(frame, Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);

            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);
        }

        imshow("Image",frame);
        waitKey(0);
    }

    destroyAllWindows();

    Mat cameraMatrix,distCoeffs,R,T;

    /*
    * Performing camera calibration by 
    * passing the value of known 3D points (objpoints)
    * and corresponding pixel coordinates of the 
    * detected corners (imgpoints)
    */
    calibrateCamera(objpoints, imgpoints, Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);

    cout << "cameraMatrix : " << cameraMatrix << endl;
    cout << "distCoeffs : " << distCoeffs << endl;
    cout << "Rotation vector : " << R << endl;
    cout << "Translation vector : " << T << endl;

    return 0;
}
