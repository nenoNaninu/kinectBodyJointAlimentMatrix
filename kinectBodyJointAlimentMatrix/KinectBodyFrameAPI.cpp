#include"KinecBodyFrameAPI.h"
#include<vector>
#include"ComPtr.h"
#include<iostream>
#include <thread>
#include<ppl.h>

//void ERROR_CHECK(HRESULT ret) {
//	if ((ret) != S_OK) {
//		std::stringstream ss;
//		ss << "failed " << std::hex << ret << std::endl;
//		throw std::runtime_error(ss.str().c_str());
//	}
//}

#define ERROR_CHECK( ret )  \
    if ( (ret) != S_OK ) {    \
        std::stringstream ss;	\
        ss << "failed " #ret " " << std::hex << ret << std::endl;			\
        throw std::runtime_error( ss.str().c_str() );			\
    }

void KinectBodyFrameAPI::initialize() {
	KinectAPI::initialize();
	ComPtr<IBodyFrameSource> bodySource;
	ERROR_CHECK(kinectSensor->get_BodyFrameSource(&bodySource));
	ERROR_CHECK(bodySource->OpenReader(&bodyReader));

	ERROR_CHECK(kinectSensor -> get_CoordinateMapper(&coordinateMapper));
}

//6人分のジョイントを引数にコピーする関数。
void KinectBodyFrameAPI::upDateJointData() {
	ComPtr<IBodyFrame> bodyFramePtr;
	const HRESULT ret = bodyReader->AcquireLatestFrame(&bodyFramePtr);
	
	if (FAILED(ret)) {
		return;
	}
	else {
		//std::cout << "hoge" << std::endl;
		//std::getchar();
	}
	
	for (int count = 0; count < BODY_COUNT; count++) {
		ERROR_CHECK(bodyFramePtr->GetAndRefreshBodyData(BODY_COUNT, bodyPtrArray));
		BOOLEAN tracked = false;
		ERROR_CHECK(bodyPtrArray[count]->get_IsTracked(&tracked));
		isTrackedArray[count] = tracked;
		if (tracked) {
			Joint joint[JointType::JointType_Count];
			ERROR_CHECK(bodyPtrArray[count] -> GetJoints(JointType::JointType_Count,joint));
			memcpy(&jointArray[count][0],joint,sizeof(Joint[25]));
		}
	}

	//std::cout << (int)(isTrackedArray[0]) << (int)(isTrackedArray[1]) << (int)(isTrackedArray[2]) << (int)(isTrackedArray[3]) << (int)(isTrackedArray[4]) << (int)(isTrackedArray[5]) << std::endl;
}

void KinectBodyFrameAPI::getIsPlayer(int isPlayer[]) {
	for (int i = 0; i < BODY_COUNT; i++) {
		isPlayer[i] = (int)(isTrackedArray[i]);
	}
}

void KinectBodyFrameAPI::getBodyJointData(Joint argJoint[6][25]) {
	for (int i = 0; i < BODY_COUNT; i++) {
		memcpy(&argJoint[i][0],&jointArray[i][0],sizeof(Joint)*25);
	}
}

void KinectBodyFrameAPI::getJointType(int argJointType[6][25]) {
	for (int i = 0; i < BODY_COUNT; i++) {
		for (int j = 0; j < 25; j++) {
			argJointType[i][j] = jointArray[i][j].JointType;
		}
	}
}