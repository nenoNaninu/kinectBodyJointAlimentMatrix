#include"libHeader.h"
#include<iostream>
#include"KinectBodyJointVeiwer.h"
#include<opencv2\opencv.hpp>
#include<vector>
#include<fstream>

using namespace cv;
using std::vector;

std::vector<std::string> split(const std::string& line, char delimiter)
{
	std::istringstream stream(line);
	std::string filed;
	std::vector<std::string> result;
	while (std::getline(stream, filed, delimiter))
	{
		result.push_back(filed);
	}
	return result;
}


int main()
{
	Mat mat;
	KinectBodyJointVeiwer kbj;
	kbj.initialize();
	int height = kbj.getColorHeight();
	int width = kbj.getColorWidth();
	mat = Mat(height, width, CV_8UC4);
	char key = 0;
	vector<Point2f> srcPoints(4);
	vector<Point2f> dstPoints(4);
	int i = 0;

	std::cout << "Unityの座標系と合わせますよ。" << std::endl;
	std::cout << "撮りたい座標に立ったらsを押す。" << std::endl;
	std::cout << "4点とって、その値でよければc,やり直したいならその他を押す。" << std::endl;

	while (key != 'q')
	{
		key = waitKey(1);
		kbj.update();
		kbj.imshowBodyJoint(mat);
		cv::resize(mat, mat, cv::Size(mat.cols / 2, mat.rows / 2));
		imshow("view", mat);

		if (key == 's')//set
		{
			if (kbj.getPlayerNum() == 1)
			{
				float x, y;
				std::tie(x, y) = kbj.getCameraSpacePlayerPositionPosition();
				srcPoints[i].x = x;
				srcPoints[i].y = y;
				std::cout << "cameraSpace x:" << srcPoints[i].x << " y:" << srcPoints[i].y << std::endl;
				i++;
				if (i == 4)
				{
					std::cout << "とりあえず4点取り終えました。" << std::endl;
					std::cout << "cかなにかを押してください。" << std::endl;
					key = waitKey(0);
					if (key == 'c')
					{
						destroyAllWindows();
						break;
					}
					else
					{
						i = 0;
						continue;
					}
				}
			}
		}

	}//while

	std::cout << "ファイルを読みこみます ファイルの準備ができたらファイル名を入力してください" << std::endl;
	std::string fileName;
	std::cin >> fileName;

	std::ifstream ifs(fileName);
	std::string line;
	i = 0;
	while (std::getline(ifs, line))
	{
		std::vector<std::string> temp = split(line, ',');

		dstPoints[i].x = std::stod(temp[0]);
		dstPoints[i].y = std::stod(temp[1]);
		i++;
		if (i == 4)
		{
			break;
		}
	}

	Mat homographyMat = findHomography(srcPoints,dstPoints);
	std::cout << "homographyMatrix is " << std::endl;
	std::cout << homographyMat << std::endl;
	Mat homography32F;
	homographyMat.convertTo(homography32F, CV_32FC1);

	float* homographyPtr = (float*)homography32F.data;

	std::ofstream ofs("homography.csv");

	ofs << homographyPtr[0] << "," << homographyPtr[1] << "," << homographyPtr[2] << std::endl;
	ofs << homographyPtr[3] << "," << homographyPtr[4] << "," << homographyPtr[5] << std::endl;
	ofs << homographyPtr[6] << "," << homographyPtr[7] << "," << homographyPtr[8] << std::endl;

	return 0;
}