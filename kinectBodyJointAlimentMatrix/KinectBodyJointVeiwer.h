#pragma once
#include"KinecBodyFrameAPI.h"

class KinectBodyJointVeiwer :public KinectBodyFrameAPI
{
public:
	void initialize();
	void imshowBodyJoint(cv::Mat&);
	void update();
};