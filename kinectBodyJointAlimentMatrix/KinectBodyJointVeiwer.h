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

	//�J�����X�y�[�X��̃v���C���[��spine��x,z��Ԃ��֐��B
	std::tuple<float, float> getCameraSpacePlayerPositionPosition();

	int getPlayerNum();
};