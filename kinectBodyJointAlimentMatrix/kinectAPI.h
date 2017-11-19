#pragma once

#include<Kinect.h>
#include<vector>
#include<iostream>
#include<sstream>
#include<opencv2\core.hpp>

#define ERROR_CHECK( ret )  \
    if ( (ret) != S_OK ) {    \
        std::stringstream ss;	\
        ss << "failed " #ret " " << std::hex << ret << std::endl;			\
        throw std::runtime_error( ss.str().c_str() );			\
    }


class KinectAPI
{

protected:

	IKinectSensor* kinectSensor = nullptr;
	IDepthFrameReader* depthFrameReader = nullptr;
	IColorFrameReader* colorFrameReader = nullptr;

	std::vector<UINT16> depthBuffer;

	cv::Mat depthImage;
	cv::Mat colorImage;

	const char* DepthWindowName = "Depth Image";

	int depthWidth;
	int depthHight;

	int colorWidth;
	int colorHeight;
	int colorBytesPerPixel;
public:
	~KinectAPI() {
		if (kinectSensor != nullptr) {
			kinectSensor->Close();
			kinectSensor = nullptr;
		}
	}
	void initialize();

	void queryDepthImage(cv::Mat& mat);
	void queryColorImage(cv::Mat& mat);

	void upDateImage();

	int getDepthWidth();
	int getDepthHeight();

	int getColorWidth();
	int getColorHeight();
	int getColorBytesPerPixcel();

};