#include"libHeader.h"
#include<iostream>
#include"KinectBodyJointVeiwer.h"
#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	Mat mat;
	KinectBodyJointVeiwer kbj;
	kbj.initialize();
	int height = kbj.getColorHeight();
	int width = kbj.getColorWidth();
	mat = Mat(height, width, CV_8UC4);
	char key = 0;
	while (key != 'q')
	{
		kbj.update();
		kbj.imshowBodyJoint(mat);
		imshow("img", mat);
	 	key = waitKey(1);
	}

	return 0;
}