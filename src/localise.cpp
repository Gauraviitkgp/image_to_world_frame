#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;
#define rangie 5

Mat hsv_img;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void mouseCB(int event, int x, int y, int flags, void* userdata)
{
 if  ( event == EVENT_LBUTTONDOWN )
 {
    cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    cout << (int)hsv_img.at<Vec3b>(y,x)[0] << " " << (int)hsv_img.at<Vec3b>(y,x)[1] << " " << (int)hsv_img.at<Vec3b>(y,x)[2] << endl;
  }
}

Mat eroded(Mat src,int erosion_size)
{
	int erosion_type;
	erosion_type = MORPH_RECT;
	Mat element = getStructuringElement( erosion_type,
	                               Size( 2*erosion_size + 1, 2*erosion_size+1 ),
	                               Point( erosion_size, erosion_size ) );

	erode(src,src,element);			
	return src;
}


int main(int argc, char** argv)
{

	char a=*argv[2];

	Mat grid_thr, no_grid, white_thr,grid_line;
	int h=171,s=40,v=200,ht=102,st=48;
	int r_w=255, g_w=255,b_w=255, rt_w=39, gt_w=26,bt_w=66;
	int kernel_size=1;

	namedWindow("Sliders");
	namedWindow("MainIM", CV_WINDOW_NORMAL);

	setMouseCallback("MainIM", mouseCB, NULL);
	createTrackbar("H","Sliders",&h,255);
	createTrackbar("S","Sliders",&s,255);
	//createTrackbar("V","Sliders",&v,255);
	createTrackbar("HT","Sliders",&ht,255);
	createTrackbar("ST","Sliders",&st,255);

	createTrackbar("r_w","Sliders",&r_w,255);
	createTrackbar("g_w","Sliders",&g_w,255);
	createTrackbar("b_w","Sliders",&b_w,255);
	//createTrackbar("V_w","Sliders",&v_w,255);
	createTrackbar("rt_w","Sliders",&rt_w,255);
	createTrackbar("gt_w","Sliders",&gt_w,255);
	createTrackbar("bt_w","Sliders",&bt_w,255);

	//createTrackbar("min_thresh","Sliders",&min_thresh,255);
	//createTrackbar("max_thresh","Sliders",&max_thresh,255);
	createTrackbar("kernel_size","Sliders",&kernel_size,2);

	// createTrackbar("H_G","Sliders",&h_g,255);
	// createTrackbar("S_G","Sliders",&s_g,255);
	// //createTrackbar("V_G","Sliders",&v_g,255);
	// createTrackbar("HT_G","Sliders",&ht_g,255);
	// createTrackbar("ST_G","Sliders",&st_g,255);

	// createTrackbar("H_R","Sliders",&h_r,255);
	// createTrackbar("S_R","Sliders",&s_r,255);
	// //createTrackbar("V_R","Sliders",&v_r,255);
	// createTrackbar("HT_R","Sliders",&ht_r,255);
	// createTrackbar("ST_R","Sliders",&st_r,255);

	if (a=='i')
	{
		Mat img=imread(argv[1],CV_LOAD_IMAGE_COLOR);

		namedWindow("grid_thr",CV_WINDOW_NORMAL);
		namedWindow("white_thr",CV_WINDOW_NORMAL);
		namedWindow("grid_line",CV_WINDOW_NORMAL);
	
		cvtColor(img, hsv_img, CV_BGR2HSV_FULL);

		imshow("MainIM",img);
		
		while(1)
		{
			inRange(hsv_img,Scalar(h-ht,s-st,0), Scalar(h+ht,s+st,255),grid_thr);
			inRange(img,Scalar(r_w-rt_w,g_w-gt_w,b_w-bt_w), Scalar(r_w+rt_w,g_w+gt_w,b_w+bt_w),white_thr);
			
			bitwise_not(grid_thr,no_grid);
			bitwise_and(no_grid,white_thr,grid_line);

			Mat dst,cdst;
			Canny(grid_line,dst,0, 255,(kernel_size+1)*2+1);
			cvtColor(dst, cdst, CV_GRAY2BGR);

			#if 1
				vector<Vec2f> lines;
				HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
				float *x1=new float[lines.size()];
				float *x2=new float[lines.size()];
				for( size_t i = 0; i < lines.size(); i++ )
				{
					float rho = lines[i][0], theta = lines[i][1];
					Point pt1, pt2;
					double a = cos(theta), b = sin(theta);
					double x0 = a*rho, y0 = b*rho;
					pt1.x = cvRound(x0 + 1000*(-b));
					pt1.y = cvRound(y0 + 1000*(a));
					pt2.x = cvRound(x0 - 1000*(-b));
					pt2.y = cvRound(y0 - 1000*(a));
					line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
					cout<<"x1:"<<pt1.x<<"	x2:"<<pt2.x<<"	y1:"<<pt1.y<<"	y2:"<<pt2.y;
					cout<<"	rho:"<<rho<<"	theta:"<<theta<<endl;
			  	}
			  	cout<<endl;
			#else
			vector<Vec4i> lines;
			HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
			for( size_t i = 0; i < lines.size(); i++ )
			{
				Vec4i l = lines[i];
				line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
			}
			#endif	
			//grid_line=eroded(grid_line,1);
			//dilate(grid_area,grid_area,element);

			cout<<lines.rho[2];
			imshow("grid_thr",grid_thr);
			//imshow("no_grid",no_grid);
			imshow("white_thr",white_thr);
			imshow("grid_line",grid_line);
			imshow("detected lines", cdst);
			imwrite("../images/grid_line.jpg",grid_line);
			imshow("dst",dst);
			
			waitKey(33);
	   }
	}
  // else
  // {
		// VideoCapture cap(argv[1]);
		// namedWindow("grid_thr", CV_WINDOW_NORMAL );
		// namedWindow("white_thr", CV_WINDOW_NORMAL );
		// namedWindow("rb", CV_WINDOW_NORMAL );
		// namedWindow("gb", CV_WINDOW_NORMAL );
		// namedWindow("allb", CV_WINDOW_NORMAL );
		// namedWindow("detect", CV_WINDOW_NORMAL );
		// namedWindow("hsv_img", CV_WINDOW_NORMAL );
		// namedWindow("grid_area", CV_WINDOW_NORMAL);

		// int cont=0;
		// float stored[10][2][3];
		// int count[rangie]={0,0,0,0,0};
		// while(1)
		// {

		// Mat img;
		// cap >> img;

		// cvtColor(img, hsv_img, CV_BGR2HSV_FULL);

		// if (img.empty())
		// break;

		// imshow( "MainIM", img );

		// inRange(hsv_img,Scalar(h-ht,s-st,0), Scalar(h+ht,s+st,255),grid_thr);
		// inRange(img,Scalar(r_w-rt_w,g_w-gt_w,b_w-bt_w), Scalar(r_w+rt_w,g_w+gt_w,b_w+bt_w),white_thr);
		// inRange(hsv_img,Scalar(h_g-ht_g,s_g-st_g,0), Scalar(h_g+ht_g,s_g+st_g,255),gb_thr);
		// inRange(hsv_img,Scalar(h_r-ht_r,s_r-st_r,0), Scalar(h_r+ht_r,s_r+st_r,255),rb_thr);

		// Mat detect,src_gray,grid_area;

		// bitwise_or(grid_thr, white_thr, grid_thr);

		// int erosion_type;
		// erosion_type = MORPH_RECT;
		// int erosion_size=8; //size of the kernel will be erosion_size*2+1
		// Mat element = getStructuringElement( erosion_type,
		//                                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		//                                Point( erosion_size, erosion_size ) );

		// dilate(grid_thr,grid_area,element);
		// dilate(grid_area,grid_area,element);


		// //bitwise_or(grid_thr,grid_area,grid_thr);
		// bitwise_not(grid_thr, no_grid);
		// bitwise_and(no_grid,grid_area,no_grid);
		// bitwise_and(no_grid, gb_thr, gb);
		// bitwise_and(no_grid, rb_thr, rb);


		// //GaussianBlur( allb, allb, Size(9, 9), 0, 0 );

		// erosion_size=2; 
		// element = getStructuringElement( erosion_type,
		//                                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		//                                Point( erosion_size, erosion_size ) );

		// erode( rb, rb , element );
		// erode( rb, rb , element );
		// erode( rb, rb , element );
		// dilate( rb, rb , element );
		// dilate( rb, rb , element );
		// dilate( rb, rb , element );
		// dilate( rb, rb , element );
		// dilate( rb, rb , element );
		// dilate( rb, rb , element );
		// erosion_size=1;
		// element = getStructuringElement( erosion_type,
		//                                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		//                                Point( erosion_size, erosion_size ) );
		// erode( gb, gb , element );
		// erode( gb, gb , element );
		// erode( gb, gb , element );
		// erosion_size=1;
		// element = getStructuringElement( erosion_type,
		//                                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
		//                                Point( erosion_size, erosion_size ) );
		// dilate( gb, gb , element );
		// dilate( gb, gb , element );
		// dilate( gb, gb , element );

		// bitwise_or(rb, gb, allb);
		// allb.copyTo(detect);
		// allb.copyTo(src_gray);

		// Mat canny_output;
		// vector<vector<Point> > contours;
		// vector<Vec4i> hierarchy;

		// /// Detect edges using canny
		// Canny( src_gray, canny_output, thresh, thresh*2, 3 );
		// /// Find contours
		// findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		// Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
		// /// Draw contours
		// int at[250][2]={0};
		// int ct=0;
		// //cout<<"\nSize:"<<contours.size()<<endl;
		// for(int i=0;i<contours.size();i++)
		// {
		// int sumx=0;
		// int sumy=0;
		// if(contours[i].size()>30)
		// {
		//   for(int j=0;j<contours[i].size();j++)
		//   {
		//     sumx+=contours[i][j].x;
		//     sumy+=contours[i][j].y;
		//   }
		//   int b=sumx/contours[i].size();
		//   int c=sumy/contours[i].size();
		//   int k;
		//   for(k=0;k<contours.size();k++)
		//   {
		//     if(abs(b-at[k][0])+abs(c-at[k][1])<100)
		//       break;
		//   }
		//   if(k==contours.size())
		//   {
		   
		//     at[ct][0]=b;
		//     at[ct++][1]=c;
		//   }
		// }
		// }

		// for(int i=0;i<ct;i++)
		// {
		// //cout<<at[i][0]<<","<<at[i][1]<<endl;
		// circle(detect, Point(at[i][0],at[i][1]),50, Scalar(255,255,255),3, 8,0);
		// }
		// for( int i = 0; i< contours.size(); i++)
		// {
		// Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		// drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		// }

		// namedWindow( "Contours", CV_WINDOW_NORMAL );
		// imshow( "Contours", drawing );
		// //cout<<endl;      
		// //imshow("no_grid", no_grid);
		// imshow("grid_thr", grid_thr);
		// imshow("white_thr", white_thr);
		// imshow("rb", rb);
		// imshow("gb", gb);
		// imshow("allb", allb);
		// imshow("detect",detect);
		// imshow("grid_area",grid_area);
		// //imshow("hsv_img",hsv_img);
		// imwrite("../images/grid_thr.jpg",grid_thr);
		// imwrite("../images/MainIM.jpg",img);
		// imwrite("../images/rb.jpg",rb);
		// imwrite("../images/gb.jpg",gb);
		// imwrite("../images/allb.jpg",allb);
		// cont++;
		// waitKey(100);
  //   }

	// cap.release();

	// destroyAllWindows();

 //  }
  return 0;
}
//Feedback:- /mavros/local_postition/pose (postitons) /odem (with orientation)
// pose.pose.position.x