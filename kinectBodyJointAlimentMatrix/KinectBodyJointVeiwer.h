#pragma once
#include"KinecBodyFrameAPI.h"
#include<tuple>

class KinectBodyJointVeiwer :public KinectBodyFrameAPI
{
private:
	int playerCount;
	
public:
	void initialize();
	void imshowBodyJoint(cv::Mat&);
	void update();

	//カメラスペース上のプレイヤーのspineのx,zを返す関数。
	std::tuple<float, float> getCameraSpacePlayerPositionPosition();

	int getPlayerNum();
};