#include <stdio.h>
#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;
double addy=100,paddy=200;

void mouseCB(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN )
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		addy=(double)x;
		paddy=(double)y;
	}
}

int main(int argc, char const *argv[])
{
	Mat img=imread(argv[1],CV_LOAD_IMAGE_COLOR);
	namedWindow("Show", CV_WINDOW_NORMAL );

	Mat rvec(1,3,DataType<double>::type);
	Mat tvec(1,3,DataType<double>::type);
	Mat rotationMatrix(3,3,DataType<double>::type);
	Mat rotationMatrix2(3,3,DataType<double>::type);
	Mat distCoeffs(4,1,DataType<double>::type);
	Mat cameraMatrix(3,3,DataType<double>::type);
	Mat camera_cor(1,3,DataType<double>::type);

	setIdentity(cameraMatrix);
	cameraMatrix.at<double>(0,0)=cameraMatrix.at<double>(1,1)=554.594;
	cameraMatrix.at<double>(0,2)=320.5;
	cameraMatrix.at<double>(1,2)=180.5;
	distCoeffs.at<double>(0) = 0;
	distCoeffs.at<double>(1) = 0;
	distCoeffs.at<double>(2) = 0;
	distCoeffs.at<double>(3) = 0;
	cout<<endl<<"Camera Matrix: "<<endl<<cameraMatrix<<endl;

	rvec.at<double>(0,0)=1.76901011450686;
	rvec.at<double>(0,1)=-1.765293277548755;
	rvec.at<double>(0,2)=0.7166833678408217;
	camera_cor.at<double>(0,0)=2.4-0.041;
	camera_cor.at<double>(0,1)=2.3-0.05;
	camera_cor.at<double>(0,2)=1.8-0.1;
	Rodrigues(rvec,rotationMatrix);

	cout<<endl<<"Rvec:" << rvec<<endl;
	cout<<endl<<"camera_cor: "<<camera_cor<<endl;
	cout<<endl<<"rotationMatrix: "<<rotationMatrix<<endl;

	rotationMatrix2=rotationMatrix.t();
	rotationMatrix2=rotationMatrix2.inv();
	tvec=-rotationMatrix2*camera_cor.t();

	cout<<endl<<"tvec: "<<tvec<<endl;	
	setMouseCallback("Show", mouseCB, NULL);

	while(1)
	{	
	    Mat uvPoint = Mat::ones(3,1,DataType<double>::type); //u,v,1
		uvPoint.at<double>(0,0) = addy; //img point for which we want its real coordinates
		uvPoint.at<double>(1,0) = paddy;
		
		Mat tempMat, tempMat2;
		
		double s;
		tempMat = rotationMatrix.inv() * cameraMatrix.inv() * uvPoint;
		tempMat2 = rotationMatrix.inv() * tvec;
		s = 0 + tempMat2.at<double>(2,0);
		s /= tempMat.at<double>(2,0);

		cout << "\nP = " << rotationMatrix.inv() * (s * cameraMatrix.inv() * uvPoint - tvec) << endl;
	
		cout<<endl;
		imshow("Show",img);
		waitKey(1000);
	}
}