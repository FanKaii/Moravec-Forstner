#ifndef FEATURE_DETECTOR_H_
#define FEATURE_DETECTOR_H_

#include <opencv.hpp>

#include <vector>
#include <random>
#include <memory>

namespace fd 
{
	using uint_8 = unsigned char;

	/*
	* ����������
	*/
	class FeatureDetector
	{
	public:
		FeatureDetector() = default;
		FeatureDetector(const int &cellSize, const int &blockSize) :m_cellSize(cellSize), m_blockSize(blockSize) {}

		virtual ~FeatureDetector() = default;

		/*
		* ���������ͣ����������ꡢ���id���Լ������Ϣ������Ȥֵ��
		*/
		class KeyPoint
		{
		public:
			cv::Point2f point;
			size_t id;
			std::vector<double> info;
		};

		virtual FeatureDetector &setWinSize(const int &cellSize, const int &blockSize)     //�����������ڴ�С��cellSize<=blockSize
		{
			m_cellSize = cellSize; 
			if (cellSize > blockSize)
				m_blockSize = cellSize;
			else
				m_blockSize = blockSize;

			return *this; 
		}

		/*
		* �������ӿڣ��������Ϊ��Ҫ���м���image������Ϊ��ͨ�����ߵ�ͨ��
		*/
		virtual const std::vector<KeyPoint> &detect(const cv::Mat &inputImg) = 0;
		virtual const std::vector<KeyPoint> &getKeyPoints()const { return m_pts; }

        /*
		* ���ݼ�����������õ��������㣬����ͼ����Ϊ��ͨ����ͨ��
		*/
		virtual void drawKeyPoints(const cv::Mat &inputImg, cv::Mat &outputImg)const;

	protected:
		int m_cellSize = 5;     //��Ԫ���ڵĴ�С������5*5��
		int m_blockSize = 20;    //�鴰�ڵĴ�С�����ڵ��ڵ�Ԫ���ڣ�

		std::vector<KeyPoint> m_candidatePts;              //��ѡ��
		std::vector<KeyPoint> m_pts;                       //���õ��������㣬��getKeyPoints()��ȡ

		virtual void detectCandidatePoints(const cv::Mat &) = 0;       //���õ���ѡ��
		virtual void filterKeyPoints(const cv::Mat &) = 0;             //���˵õ�������
	};
}

namespace fd
{
	inline void FeatureDetector::drawKeyPoints(const cv::Mat &inputImg, cv::Mat &outputImg)const
	{
		outputImg = inputImg.clone();

		static std::default_random_engine e;
		static std::uniform_int_distribution<int> u(0, 255);

		if (outputImg.channels() == 1)
			cv::cvtColor(outputImg, outputImg, CV_GRAY2BGR);

		for (auto it = m_pts.cbegin(); it != m_pts.cend(); ++it)
			cv::circle(outputImg, it->point, 2, cv::Scalar(u(e), u(e), u(e)));
	}
}

#endif
