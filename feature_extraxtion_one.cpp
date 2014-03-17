/*
	This code is a very raw feature extractor from any image.
	Main extractions are: 1.Channel creation on CIE-LUV color space
						  2.Channel creation on gradient basis with two sigmas(0 and 0.5)
						  3.Channel creation on orientation basis (angles are 0 45 90 and 135 in degrees)

	Note:Will make changes to orientation channeling soon

	Usage : ./feature_extraction_one.cpp IMAGE_NAME.ECTENSION

*/
 





#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class luvsplit                       //splitter on basis of LUV color space
{
	protected:
		Mat image;
		Mat channel[3];
		
		

	public:
		Mat luv_1;
		Mat luv_2;
		Mat luv_3;
		void getimage(Mat src) //storing image into a class variable named image
    {              
 
      	if(! src.data )                             
      	{
      	    cout <<  "src not filled" << endl ;
        }
 	
      	else
      	{
      	    image = src.clone();
      	    cout << "got image" <<endl;
      	 }
    }	
		
		void splitchannel()
		{
			Mat channels[3];			
			split(image,channels);
			channel[0] = channels[0];
			channel[1] = channels[1];
			channel[2] = channels[2];
		}
			
		void lsplit()
		{
			
			channel[2]=Mat::zeros(image.rows, image.cols, CV_8UC1);
	    channel[1]=Mat::zeros(image.rows, image.cols, CV_8UC1);
      merge(channel,3,luv_1);
		}

		void usplit()
		{
			
			channel[0]=Mat::zeros(image.rows, image.cols, CV_8UC1);
	    channel[2]=Mat::zeros(image.rows, image.cols, CV_8UC1);
      merge(channel,3,luv_2);
		}

		void vsplit()
		{
			
			channel[0]=Mat::zeros(image.rows, image.cols, CV_8UC1);
	    channel[1]=Mat::zeros(image.rows, image.cols, CV_8UC1);
      merge(channel,3,luv_3);
		}

};
		
			

int main()
{
	Mat image = imread("left.jpg");

	//Channel creation on CIE-LUV color space

	Mat img;	
	cvtColor(image, img, CV_BGR2Luv);
	Mat channel[3];
	Mat luv_1;
	Mat luv_2;
	Mat luv_3;
	luvsplit ls;
	ls.getimage(img);
	ls.splitchannel();
	ls.lsplit();
	ls.splitchannel();
	ls.usplit();
	ls.splitchannel();
	ls.vsplit();
	ls.splitchannel();
	Mat luv1 = ls.luv_1;
	Mat luv2 = ls.luv_2;
	Mat luv3 = ls.luv_3;


	//Channel creation on gradient basis with two sigmas(0 and 0.5)
	

	Mat gaus_1;
	Mat gaus_2;
	GaussianBlur(image,gaus_1,Size(5,5),0,0,BORDER_DEFAULT);
	GaussianBlur(image,gaus_2,Size(5,5),0.5,0.5,BORDER_DEFAULT);
	



	//Channel creation on orientation basis (angles are 0 45 90 and 135 in degrees)
	
	Mat kernel1 = getGaborKernel(Size(21,21),5.0,0,10.0,0.5,0,CV_32F);
	Mat kernel2 = getGaborKernel(Size(21,21),5.0,45,10.0,0.5,0,CV_32F);
	Mat kernel3 = getGaborKernel(Size(21,21),5.0,90,10.0,0.5,0,CV_32F);
	Mat kernel4 = getGaborKernel(Size(21,21),5.0,135,10.0,0.5,0,CV_32F);
	Mat gaus_1_1;
	Mat gaus_1_2;
	Mat gaus_1_3;
	Mat gaus_1_4;
	Mat gaus_2_1;
	Mat gaus_2_2;
	Mat gaus_2_3;
	Mat gaus_2_4;
	filter2D(gaus_1,gaus_1_1,CV_32F,kernel1);
	filter2D(gaus_1,gaus_1_2,CV_32F,kernel2);
	filter2D(gaus_1,gaus_1_3,CV_32F,kernel3);
	filter2D(gaus_1,gaus_1_4,CV_32F,kernel4);
	filter2D(gaus_1,gaus_2_1,CV_32F,kernel1);
	filter2D(gaus_1,gaus_2_2,CV_32F,kernel2);
	filter2D(gaus_1,gaus_2_3,CV_32F,kernel3);
	filter2D(gaus_1,gaus_2_4,CV_32F,kernel4);


	
	
	return 0;
}

	

	
