
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;
double addy,paddy;

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

	vector<Point2f> imagePointsPix;
	vector<Point3f> objectPointsm;

//	imagePointsPix.push_back(Point2f(0.,284.));
	//imagePointsPix.push_back(Point2f(146.,283.));
	//imagePointsPix.push_back(Point2f(307.,283.));
	//imagePointsPix.push_back(Point2f(360.,282.));
//	imagePointsPix.push_back(Point2f(624.,281.));
//	imagePointsPix.push_back(Point2f(40.,173.));	
	 imagePointsPix.push_back(Point2f(105.,161.));
	imagePointsPix.push_back(Point2f(299.,164.));
	imagePointsPix.push_back(Point2f(510.,164.));
	//imagePointsPix.push_back(Point2f(619.,276.));
	// imagePointsPix.push_back(Point2f(28.,176.));
	 imagePointsPix.push_back(Point2f(150.,52.));
	imagePointsPix.push_back(Point2f(299.,52.));
	imagePointsPix.push_back(Point2f(472.,52.));
	//imagePointsPix.push_back(Point2f(566.,171.));
//	imagePointsPix.push_back(Point2f(636.,96.));
//	imagePointsPix.push_back(Point2f(12.,36.));
	// imagePointsPix.push_back(Point2f(187.,96.));
	// imagePointsPix.push_back(Point2f(187.,91.));
	// imagePointsPix.push_back(Point2f(307.,89.));
	// imagePointsPix.push_back(Point2f(408.,96.));
	// imagePointsPix.push_back(Point2f(529.,89.));
	// imagePointsPix.push_back(Point2f(636.,86.));


	//objectPointsm.push_back(Point3f(1., 2., 0.));
	//objectPointsm.push_back(Point3f(1., 1., 0.));
	//objectPointsm.push_back(Point3f(1.,-0., 0.));
	//objectPointsm.push_back(Point3f(1., -1., 0.));
	//objectPointsm.push_back(Point3f(1., -2., 0.));
	//objectPointsm.push_back(Point3f(2., 2., 0.));
	objectPointsm.push_back(Point3f(2., 4., 0.));
	objectPointsm.push_back(Point3f(2.,3., 0.));
	objectPointsm.push_back(Point3f(2., 2., 0.));
	//objectPointsm.push_back(Point3f(2., -2., 0.));
	//objectPointsm.push_back(Point3f(3., 2., 0.));
	objectPointsm.push_back(Point3f(3., 4., 0.));
	objectPointsm.push_back(Point3f(3.,3., 0.));
	objectPointsm.push_back(Point3f(3., 2., 0.));
	//objectPointsm.push_back(Point3f(3., -2., 0.));
	//objectPointsm.push_back(Point3f(3., -3., 0.));
	//objectPointsm.push_back(Point3f(4., 3., 0.));
	// objectPointsm.push_back(Point3f(4., 2., 0.));
	// objectPointsm.push_back(Point3f(4., 1., 0.));
	// objectPointsm.push_back(Point3f(4.,0., 0.));
	// objectPointsm.push_back(Point3f(4., -1., 0.));
	// objectPointsm.push_back(Point3f(4., -2., 0.));
	// objectPointsm.push_back(Point3f(4., -3., 0.));

	Mat rvec(1,3,DataType<double>::type);
	Mat tvec(1,3,DataType<double>::type);
	Mat rotationMatrix(3,3,DataType<double>::type);
	Mat rotationMatrix2(3,3,DataType<double>::type);
	Mat distCoeffs(4,1,DataType<double>::type);
	Mat cameraMatrix(3,3,DataType<double>::type);	
	Mat inlin;
	setIdentity(cameraMatrix);
	cameraMatrix.at<double>(0,0)=cameraMatrix.at<double>(1,1)=554.594;
	cameraMatrix.at<double>(0,2)=320.5;
	cameraMatrix.at<double>(1,2)=180.5;
	distCoeffs.at<double>(0) = 0;
	distCoeffs.at<double>(1) = 0;
	distCoeffs.at<double>(2) = 0;
	distCoeffs.at<double>(3) = 0;
	cout<<cameraMatrix<<endl;

	// int x=atoi(argv[2]);
	// int min=31414,cont;
	// for(int j=1;j<x;j++)
	// {
	// 	solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, j,0.1,0.95	,inlin,CV_P3P);

	// 	Rodrigues(rvec,rotationMatrix);
	
	// 	vector<Point2f> projectedPoints;

	// 	projectPoints(objectPointsm, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);
	// 	double sum=0;
	// 	for(int i = 0; i < projectedPoints.size(); ++i)
	// 	{
 //    		sum+=abs(projectedPoints[i].x-imagePointsPix[i].x)+abs(projectedPoints[i].y-imagePointsPix[i].y);
	// 	}
	// 	if(sum<min)
	// 	{
	// 		min=sum;
	// 		cont=j;
	// 	}
 //    //cout<<"\nSUM: "<<sum<<endl<<endl;
	// 	cout<<"J: "<<j<<" SUM: "<<sum<<" MIN:"<<min<<endl;
	// }
	// cout<<"Count:"<<cont<< " "<<"MIN:"<<min;

	// solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, cont,0.1,0.95	,inlin,CV_P3P);
	// Rodrigues(rvec,rotationMatrix);

	setMouseCallback("Show", mouseCB, NULL);
	//int y=atoi(argv[3]);
	#if 1
		int x=atoi(argv[2]);
		int min=31414,cont;
		cout<<"Hi"<<endl<<endl;
		for(int j=1;j<x;j++)
		{

			solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, j,0.1,0.95	,inlin,CV_P3P);

			Rodrigues(rvec,rotationMatrix);
		
			vector<Point2f> projectedPoints;

			projectPoints(objectPointsm, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);
			double sum=0;
			for(int i = 0; i < projectedPoints.size(); ++i)
			{
	    		sum+=abs(projectedPoints[i].x-imagePointsPix[i].x)+abs(projectedPoints[i].y-imagePointsPix[i].y);
			}
			if(sum<min)
			{
				min=sum;
				cont=j;
			}
		}

		solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, cont,0.1,0.95	,inlin,CV_P3P);
		Rodrigues(rvec,rotationMatrix);

		cout<<"Rvec:"<<rvec<<endl;
		cout<<"tvec:"<<tvec<<endl;
		cout<<"Camera Cordinates "<<-rotationMatrix.t()*tvec;
		while(1)
		{	

		    Mat uvPoint = Mat::ones(3,1,DataType<double>::type); //u,v,1
			uvPoint.at<double>(0,0) = addy; //img point for which we want its real coordinates
			uvPoint.at<double>(1,0) = paddy;
			
			Mat tempMat, tempMat2;
			
			double s;
			tempMat = rotationMatrix.inv() * cameraMatrix.inv() * uvPoint;
			tempMat2 = rotationMatrix.inv() * tvec;

			s = 0 + tempMat2.at<double>(2,0); //before 0 it was 285, which represents the height Zconst
			s /= tempMat.at<double>(2,0);
			Mat output=s*uvPoint;

			cout << "\nP = " << rotationMatrix.inv() * (s * cameraMatrix.inv() * uvPoint - tvec) << endl;
			
			setMouseCallback("Show", mouseCB, NULL);
			cout<<endl;
			imshow("Show",img);
			waitKey(1000);
		}
	#else 
	{
		int x=atoi(argv[2]);
		int min=31414,cont;
		for(int j=1;j<x;j++)
		{
			solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, j,0.1,0.95	,inlin,CV_P3P);

			Rodrigues(rvec,rotationMatrix);
		
			vector<Point2f> projectedPoints;

			projectPoints(objectPointsm, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);
			double sum=0;
			for(int i = 0; i < projectedPoints.size(); ++i)
			{
    			sum+=abs(projectedPoints[i].x-imagePointsPix[i].x)+abs(projectedPoints[i].y-imagePointsPix[i].y);
			}
			if(sum<min)
			{
				min=sum;
				cont=j;
			}
			cout<<"J: "<<j<<" SUM: "<<sum<<" MIN:"<<min<<endl;
		}
		cout<<"Count:"<<cont<< " "<<"MIN:"<<min<<endl;

		solvePnPRansac(objectPointsm, imagePointsPix, cameraMatrix, distCoeffs, rvec, tvec, 0, cont,0.1,0.95	,inlin,CV_P3P);
		Rodrigues(rvec,rotationMatrix);
		cout<<"Rvec:"<<rvec<<endl;
		cout<<"tvec:"<<tvec<<endl;

		setMouseCallback("Show", mouseCB, NULL);
		cout<<"\nCamera Cordinates "<<-rotationMatrix.t()*tvec;
		setMouseCallback("Show", mouseCB, NULL);
		cout<<endl;

		imshow("Show",img);
		waitKey(0000);	
	}
	#endif
}
/*
XYZ=002
Rvec:[1.764514762393209;
 -1.780685435244631;
 0.7325915621812246]
tvec:[-0.01909767291557224;
 1.402113009725163;
 1.462660406382692]

Camera Cordinates [-0.01626623071641831;
 -0.001813630829758148;
 2.026176990796318]



XYZ=003
Rvec:[1.745652658110562;
 -1.790957695767514;
 0.7314882833614018]
tvec:[-0.08459587385352374;
 2.068372584492771;
 2.025855824555773]

Camera Cordinates [0.05319219390911223;
 -0.08930678410844205;
 2.894582581454577]


XYZ=032
Rvec:[1.76901011450686;
 -1.765293277548755;
 0.7166833678408217]
tvec:[2.931487239060401;
 1.351367248947931;
 1.33945179956652]

Camera Cordinates [0.02341496957262601;
 2.928090952066225;
 1.907793781647503]


*/
