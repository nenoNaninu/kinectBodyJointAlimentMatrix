#include"exportDll.h"
#include"Stream.h"

void* getStream() {
	Stream* stream = new Stream();
	return stream;
}

void getBodyJoint(void* streamPtr, float argJointX[], float argJointY[], float argJointZ[]) {
	Stream* stream = (Stream*)streamPtr;
	stream->getJointPosition(argJointX, argJointY, argJointZ);
}

void releaseStream(void* streamPtr) {
	Stream* stream = (Stream*)streamPtr;
	delete stream;
}

void getIsPlayer(void* streamPtr,int isPlayer[]) {
	Stream* stream = (Stream*)streamPtr;
	stream->getIsPlayer(isPlayer);
}

void upDateStreamData(void* streamPtr) {
	Stream* stream = (Stream*)streamPtr;
	stream->update();
}

void getJointType(void* streamPtr,int argJointType[]) {
	Stream* stream = (Stream*)streamPtr;
	stream->getJointType(argJointType);
}