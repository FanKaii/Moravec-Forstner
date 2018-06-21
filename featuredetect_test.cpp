#include <opencv.hpp>
#include <iostream>

#include "moravec.h"
#include "forstner.h"

#define _MORAVEC
//#define _FORSTNER

struct DetectTest
{
	enum class DetectType
	{
		MORAVEC,
		FORSTNER,
		SIFT
	};

	bool readImage(const std::string &fileLocation     //ͼ���ļ�·��
		, bool resizeImg = false     //�Ƿ�ı�ͼ���size
		, const cv::Size &imgSize = cv::Size(640, 480)     //ͼ���size
		)
	{
		srcImg = cv::imread(fileLocation, 1);
		if (srcImg.empty())
			return false;

		if (resizeImg)
			cv::resize(srcImg, srcImg, imgSize);

		return true;
	}

	void detect_(fd::FeatureDetector *detector)
	{
		double t = cv::getTickCount();

		detector->detect(srcImg);

		t = (cv::getTickCount() - t) / cv::getTickFrequency();

		std::cout << "���μ����ʱ " << t << " ��" << std::endl;
	}

	void detect(const DetectType &type)
	{
		switch (type)
		{
		case DetectType::MORAVEC:
		{
			fd::MoravecFeatureDetector detector;

			detector.setThresh(2000).setWinSize(5, 20);                       //���ò���
			detect_(&detector);
			detector.drawKeyPoints(srcImg, resImg);
		}
		break;
		case DetectType::FORSTNER:
		{
			fd::ForstnerFeatureDetector detector;

			detector.setThreshByWeightMedian(0.9, 5).setWinSize(5, 20);      //���ò������ɵ��ò�ͬ�ӿڣ�������鿴ForstnerFeatureDetector.h
			detect_(&detector);
			detector.drawKeyPoints(srcImg, resImg);
		}
		break;
		default:
			std::cerr << "Moravec and Forstner available." << std::endl;
			exit(0);
		}
	}
	void showImg(const std::string &winName)
	{
		cv::imshow(winName, resImg);
		cv::waitKey(0);
	}

private:
	cv::Mat srcImg, resImg;
};

int main(int, char **)
{
	/*
	* �޸ļ���㷨�Ĳ�����鿴DetectTest::detect������
	*/
#ifdef _MORAVEC
	DetectTest testM;

	if (!testM.readImage("image.png"))         //��ȡͼ��Ĭ�ϲ��ı�ͼ���size
	{
		std::cerr << "image path error!" << std::endl;

		system("pause");
		return -1;
	}
	testM.detect(DetectTest::DetectType::MORAVEC);
	testM.showImg("Moravec");
#endif

#ifdef _FORSTNER
	DetectTest testF;

	if (!testF.readImage("image.png"))
	{
		std::cerr << "image path error!" << std::endl;

		system("pause");
		return -1;
	}
	testF.detect(DetectTest::DetectType::FORSTNER);
	testF.showImg("Forstner");
#endif

	system("pause");
	return 0;
}