#include"KinectBodyJointVeiwer.h"
#include<opencv2\opencv.hpp>

void KinectBodyJointVeiwer::imshowBodyJoint(cv::Mat& mat)
{
	queryColorImage(mat);
	for (int i = 0; i < 6; i++)
	{
		if (isTrackedArray[i])
		{
			++playerCount;
			for (int j = 0; j < 25; j++)
			{
				ColorSpacePoint colorSpacePoint;
				ERROR_CHECK(coordinateMapper->MapCameraPointToColorSpace(jointArray[i][j].Position, &colorSpacePoint));
				int x = static_cast<int>(colorSpacePoint.X + 0.5f);
				int y = static_cast<int>(colorSpacePoint.Y + 0.5f);
				if ((0 <= x) && (x < mat.cols) && (0 <= y) && (y < mat.rows))
				{
					cv::circle(mat, cv::Point(x, y), 10, cv::Scalar(255,0,0,1), 10);
				}
			}
		}
	}
}

void KinectBodyJointVeiwer::initialize()
{
	KinectBodyFrameAPI::initialize();
}

void KinectBodyJointVeiwer::update()
{
	upDateImage();
	upDateJointData();
}

std::tuple<float, float> KinectBodyJointVeiwer::getCameraSpacePlayerPositionPosition()
{
	for (int i = 0; i < 6; i++)
	{
		if (isTrackedArray[i])
		{
			float x = jointArray[i][JointType::JointType_SpineMid].Position.X;
			float z = jointArray[i][JointType::JointType_SpineMid].Position.Z;
			return std::make_tuple(x,z);
		}
	}
	return std::make_tuple(0.0f,0.0f);
}

int KinectBodyJointVeiwer::getPlayerNum()
{
	return playerCount;
}