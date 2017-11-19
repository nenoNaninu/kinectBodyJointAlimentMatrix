#pragma once
#include"KinecBodyFrameAPI.h"

class Stream
{
public:
	Stream() {
		kinectBodyFreame = KinectBodyFrameAPI();
		kinectBodyFreame.initialize();
	}
	~Stream(){
	}

	void update();

	//25joint*6�l���̔z��
	void getJointPosition(float[],float[],float[]);

	void getIsPlayer(int[]);

	void getJointType(int[]);

private:
	KinectBodyFrameAPI kinectBodyFreame;
};

