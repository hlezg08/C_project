// opencv_test.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define UNDISTORTION 0			// Option for undistorting images with intrinsic parameters and distortion coefficients
#define	DISPLAY_CORNER 0		// Option for displaying detected corners in checkerboard images.

using namespace cv;
using namespace std;

void print_intrinsic_matrix(Mat &cameraMatrix);
void print_rotation(Mat &Matrix);
void print_translation(Mat &Trans);
vector<Point3f> Create3DChessboardCorners(Size boardSize, float squareSize);

void type2str(int type);
//If you want to know the type of 'Mat', use the following function
//For instance, for 'Mat input'
//type2str(input.type());


int main()
{
	Size boardSize(6, 7);	// the number of corners in the checkerboard
	const float squareSize = 26.f;	//physical length of interval between corners

	char camera1_file[200], camera2_file[200];
	Mat camera1_image, camera2_image, input_gray;

	Mat cameraMatrix1 = Mat::eye(3, 3, CV_64F);
	Mat cameraMatrix2 = Mat::eye(3, 3, CV_64F);

	Mat distortionCoeff1, distortionCoeff2;
	Mat rotationMatrix, translationVector, essentialMatrix, fundamentalMatrix;

	vector<vector<Point2f>> camera1_corner_set, camera2_corner_set;
	vector<vector<Point3f>> object_points_set;




	int images_used_num = 0;		//The number of checkerboard images with correct corners

	for (int camera_num = 0; camera_num < 20; camera_num++)
	{
		printf("processing %02d images\n", camera_num);
		sprintf_s(camera1_file, "s0715_2\\left_images\\out_00_160715_%02d_l.png", camera_num);
		camera1_image = imread(camera1_file, 1);

		sprintf_s(camera2_file, "s0715_2\\right_images\\out_00_160715_%02d_r.png", camera_num);
		camera2_image = imread(camera2_file, 1);

		if (camera1_image.size() != camera2_image.size())
		{
			printf("All images must be the same size!\n");
			return -1;
		}

		// find corners of left and right images
		// Fill up here using 'findChessboardCorners'.
		vector<Point2f> camera1_corner;
		bool found1 = findChessboardCorners(camera1_image, camera1_image.size(), camera1_corner, 3);
		if (!found1)
			printf("Checkboard corners not found in the left camera %02d \n", camera_num);

		vector<Point2f> camera2_corner;
		bool found2 = findChessboardCorners(camera2_image, camera2_image.size(), camera2_corner, 3);
		if (!found2)
			printf("Checkboard corners not found in the right camera %02d \n", camera_num);

		if (!found1 || !found2)
		{
			printf("Left and right images %02d not used \n", camera_num);
			continue;
		}

		// Subpixel refinement of corners
		// Fill up here using 'cornerSubPix'.
		cornerSubPix(camera1_image, camera1_corner, Size(5,5),Size(-1,-1),TermCriteria(TermCriteria::EPS+TermCriteria::COUNT,30,0.1));
		camera1_corner_set.push_back(camera1_corner);

		cvtColor(camera2_image, input_gray, CV_RGB2GRAY);
		cornerSubPix(camera2_image, camera2_corner, Size(5, 5), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
		camera2_corner_set.push_back(camera2_corner);

#if DISPLAY_CORNER
		// display corners of left and right images
		drawChessboardCorners(camera1_image, boardSize, camera1_corner, found1);
		sprintf_s(camera1_file, "Corners_camera_%02d_l.png", camera_num);
		namedWindow(camera1_file, 1);
		imshow(camera1_file, camera1_image);
		waitKey(0);

		drawChessboardCorners(camera2_image, boardSize, camera2_corner, found2);
		sprintf_s(camera2_file, "Corners_camera_%02d_r.png", camera_num);
		namedWindow(camera2_file, 1);
		imshow(camera2_file, camera2_image);
		waitKey(0);
#endif		

		vector<Point3f> object_points;
		object_points = Create3DChessboardCorners(boardSize, squareSize);
		object_points_set.push_back(object_points);

		images_used_num++;
	}


	// The number of checkerboard images with correct corners should be more than 2.
	if (images_used_num > 2)
	{
		//Estimate initial intrinsic parameter and distortion coefficient for left and right cameras.
		vector<Mat> rvecs, tvecs;
		// Fill up here using 'calibrateCamera' for left and right cameras, respectively.
		calibrateCamera(object_points_set, camera1_corner_set, camera1_image.size(),cameraMatrix1,distortionCoeff1,rvecs,tvecs, CV_CALIB_FIX_INTRINSIC + CV_CALIB_SAME_FOCAL_LENGTH, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
		calibrateCamera(object_points_set, camera2_corner_set, camera1_image.size(), cameraMatrix2, distortionCoeff2, rvecs, tvecs, CV_CALIB_FIX_INTRINSIC + CV_CALIB_SAME_FOCAL_LENGTH, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));

		// It was found that the function below does not produce good initial guess for intrinsic parameters.
		// This may be because no distortion coefficients are estimated together.
		cameraMatrix1 = initCameraMatrix2D(object_points_set, camera1_corner_set, camera1_image.size(), 0);
		cameraMatrix2 = initCameraMatrix2D(object_points_set, camera2_corner_set, camera1_image.size(), 0);


		// 'flag' option may vary. Refer to the online documentation for more details.
		// For 'flag', use 'CV_CALIB_FIX_INTRINSIC + CV_CALIB_SAME_FOCAL_LENGTH' or 'CV_CALIB_FIX_ASPECT_RATIO + CV_CALIB_ZERO_TANGENT_DIST + CV_CALIB_SAME_FOCAL_LENGTH + CV_CALIB_RATIONAL_MODEL + CV_CALIB_FIX_K3 + CV_CALIB_FIX_K4 + CV_CALIB_FIX_K5', or default setting.
		// Fill up here using 'stereoCalibrate' for left and right cameras, respectively.
		double rms = stereoCalibrate(object_points_set, camera1_corner_set, camera2_corner_set, cameraMatrix1, distortionCoeff1, cameraMatrix2, distortionCoeff2, camera1_image.size(), rotationMatrix, translationVector, essentialMatrix, fundamentalMatrix, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6), CALIB_FIX_INTRINSIC);

		printf("\nLeft camera intrinsic parameters\n");
		print_intrinsic_matrix(cameraMatrix1);

		printf("\nRight camera intrinsic parameters\n");
		print_intrinsic_matrix(cameraMatrix2);

		printf("\nRotation matrix\n");
		print_intrinsic_matrix(rotationMatrix);

		printf("\nTranslation vector\n");
		print_translation(translationVector);

		printf("\ndone with RMS error=%lf\n", rms);
	}

	else
		printf("\nNot enough images with detected corners.\n");

#if UNDISTORTION
	// Undistortion of images
	Mat imageUndistorted;
	undistort(camera1_image, imageUndistorted, cameraMatrix1, distortionCoeff1);

	namedWindow("Original", 1);			imshow("Original", camera1_image);
	namedWindow("Undistorted", 1);		imshow("Undistorted", imageUndistorted);
	waitKey(0);
#endif


	// Stereo camera rectification ////////////////////////////////////////////

	// Estimate the rectification transform
	Mat R1, R2, P1, P2, Q;
	Rect validRoi[2];

	// Fill up here using 'stereoRectify'.
	stereoRectify(cameraMatrix1, distortionCoeff1, cameraMatrix2, distortionCoeff1, camera1_image.size(), rotationMatrix, translationVector, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, -1, Size(), 0, 0);

	Mat rmap[2][2];
	initUndistortRectifyMap(cameraMatrix1, distortionCoeff1, R1, P1, camera1_image.size(), CV_32FC1, rmap[0][0], rmap[0][1]);
	initUndistortRectifyMap(cameraMatrix1, distortionCoeff2, R2, P2, camera1_image.size(), CV_32FC1, rmap[1][0], rmap[1][1]);

	// For testing the rectification accuracy, rectify one of checkerboard images (Here, last image).
	Mat camera1_image_rectified, camera2_image_rectified;
	remap(camera1_image, camera1_image_rectified, rmap[0][0], rmap[0][1], INTER_LINEAR);
	remap(camera2_image, camera2_image_rectified, rmap[1][0], rmap[1][1], INTER_LINEAR);

	namedWindow("rectified image1");
	namedWindow("rectified image2");
	imshow("rectified image1", camera1_image_rectified);
	imshow("rectified image2", camera2_image_rectified);
	waitKey(0);

	imwrite("rect1.jpg", camera1_image_rectified);
	imwrite("rect2.jpg", camera2_image_rectified);


	return 0;
}

void print_translation(Mat &Trans)
{
	printf("%f, %f, %f\n", Trans.at<double>(0), Trans.at<double>(1), Trans.at<double>(2));
}

void print_rotation(Mat &Matrix)
{
	printf("%f, %f, %f\n, %f, %f, %f\n, %f, %f, %f\n", Matrix.at<double>(0, 0), Matrix.at<double>(0, 1), Matrix.at<double>(0, 2),
		Matrix.at<double>(1, 0), Matrix.at<double>(1, 1), Matrix.at<double>(1, 2),
		Matrix.at<double>(2, 0), Matrix.at<double>(2, 1), Matrix.at<double>(2, 2));
}

void print_intrinsic_matrix(Mat &cameraMatrix)
{
	printf("%f, %f, %f\n, %f, %f, %f\n, %f, %f, %f\n", cameraMatrix.at<double>(0, 0), cameraMatrix.at<double>(0, 1), cameraMatrix.at<double>(0, 2),
		cameraMatrix.at<double>(1, 0), cameraMatrix.at<double>(1, 1), cameraMatrix.at<double>(1, 2),
		cameraMatrix.at<double>(2, 0), cameraMatrix.at<double>(2, 1), cameraMatrix.at<double>(2, 2));
}


vector<Point3f> Create3DChessboardCorners(Size boardSize, float squareSize)
{
	// This function creates the 3D points of your chessboard in its own coordinate system

	vector<Point3f> corners;

	for (int i = 0; i < boardSize.height; i++)
	{
		for (int j = 0; j < boardSize.width; j++)
		{
			corners.push_back(Point3f(float(j*squareSize),
				float(i*squareSize), 0));
		}
	}

	return corners;
}

void type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	printf("Matrix: %s \n", r.c_str());
}