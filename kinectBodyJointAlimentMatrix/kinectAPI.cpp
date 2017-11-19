#include"kinectAPI.h"
#include"ComPtr.h"


void KinectAPI::initialize()
{
	ERROR_CHECK(GetDefaultKinectSensor(&kinectSensor));

	ERROR_CHECK(kinectSensor->Open());

	BOOLEAN isOpen = false;
	ERROR_CHECK(kinectSensor->get_IsOpen(&isOpen));

	if (!isOpen)
	{
		throw std::runtime_error("KinectSensor‚ªŠJ‚¯‚Ü‚¹‚ñ");
	}

	//DepthReader‚ÌŽæ“¾
	ComPtr<IDepthFrameSource> depthFrameSoure;
	ERROR_CHECK(kinectSensor->get_DepthFrameSource(&depthFrameSoure));
	ERROR_CHECK(depthFrameSoure->OpenReader(&depthFrameReader));

	ComPtr<IFrameDescription> depthFrameDiscription;
	ERROR_CHECK(depthFrameSoure->get_FrameDescription(&depthFrameDiscription));
	ERROR_CHECK(depthFrameDiscription->get_Width(&depthWidth));
	ERROR_CHECK(depthFrameDiscription->get_Height(&depthHight));

	depthBuffer.resize(depthWidth*depthHight);

	depthImage = cv::Mat(depthHight, depthWidth, CV_32FC1);

	ComPtr<IColorFrameSource> colorFrameSource;
	ERROR_CHECK(kinectSensor->get_ColorFrameSource(&colorFrameSource));
	ERROR_CHECK(colorFrameSource->OpenReader(&colorFrameReader));

	ComPtr<IFrameDescription> colorFrameDiscription;
	ERROR_CHECK(colorFrameSource->CreateFrameDescription(ColorImageFormat::ColorImageFormat_Bgra, &colorFrameDiscription));
	ERROR_CHECK(colorFrameDiscription->get_Height(&colorHeight));
	ERROR_CHECK(colorFrameDiscription->get_Width(&colorWidth));
	unsigned int tmpPixNum;
	ERROR_CHECK(colorFrameDiscription->get_BytesPerPixel(&tmpPixNum));
	colorBytesPerPixel = tmpPixNum;

	colorImage = cv::Mat(colorHeight, colorWidth, CV_8UC4);
}

int KinectAPI::getDepthHeight()
{
	return depthHight;
}

int KinectAPI::getDepthWidth()
{
	return depthWidth;
}

int KinectAPI::getColorHeight()
{
	return colorHeight;
}

int KinectAPI::getColorWidth()
{
	return colorWidth;
}

int KinectAPI::getColorBytesPerPixcel()
{
	return colorBytesPerPixel;
}

void KinectAPI::upDateImage()
{
	ComPtr<IDepthFrame> depthFrame;
	auto ret = depthFrameReader->AcquireLatestFrame(&depthFrame);

	if (ret != S_OK)
	{
		return;
	}

	//depthFrame->CopyFrameDataToArray(depthBuffer.size(), &depthBuffer[0]);
	ERROR_CHECK(depthFrame->CopyFrameDataToArray(depthBuffer.size(), &depthBuffer[0]));

	float* depthImagePtr = (float*)depthImage.data;

	for (int i = 0; i < depthImage.total(); i++)
	{
		depthImagePtr[i] = (float)depthBuffer[i];
	}

	ComPtr<IColorFrame> colorFrame;
	ret = colorFrameReader->AcquireLatestFrame(&colorFrame);
	if (ret != S_OK)
	{
		return;
	}

	ERROR_CHECK(colorFrame->CopyConvertedFrameDataToArray(colorHeight*colorWidth * colorBytesPerPixel, colorImage.data, ColorImageFormat::ColorImageFormat_Bgra));
}

void KinectAPI::queryDepthImage(cv::Mat& mat)
{
	depthImage.copyTo(mat);
}

void KinectAPI::queryColorImage(cv::Mat& mat)
{
	colorImage.copyTo(mat);
}