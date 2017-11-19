#include"Stream.h"

void Stream::getJointPosition(float argJointX[], float argJointY[], float argJointZ[]) {
	Joint joint[6][25];
	kinectBodyFreame.getBodyJointData(joint);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 25; j++) {
			argJointX[i * 25 + j] = -1*joint[i][j].Position.X;
			argJointY[i * 25 + j] = joint[i][j].Position.Y;
			argJointZ[i * 25 + j] = joint[i][j].Position.Z;
		}
	}
}

void Stream::getIsPlayer(int isPlayer[]) {
	kinectBodyFreame.getIsPlayer(isPlayer);
}

void Stream::update() {
	kinectBodyFreame.upDateJointData();
}

void Stream::getJointType(int argJointType[]) {
	
	int jointTypeArray[6][25];
	kinectBodyFreame.getJointType(jointTypeArray);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 25; j++) {
			argJointType[j + i * 25] = jointTypeArray[i][j];
		}
	}
}