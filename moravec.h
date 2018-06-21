#ifndef MORAVEC_FEATURE_DETECTOR_
#define MORAVEC_FEATURE_DETECTOR_

#include <opencv.hpp>
#include <cmath>

#include "FeatureDetector.h"

namespace fd
{
	class MoravecFeatureDetector : public FeatureDetector
	{
	public:
		MoravecFeatureDetector() = default;
		MoravecFeatureDetector(const int &cellSize, const int &blockSize, const int &thresh) :FeatureDetector(cellSize, blockSize), m_thresh(thresh) {}

		~MoravecFeatureDetector() = default;

		MoravecFeatureDetector &setThresh(const int &thresh) { this->m_thresh = thresh; return *this; }    //����ѡȡ��ѡ�����ֵ
		const std::vector<KeyPoint> &detect(const cv::Mat &inputImg)override;

	private:
		int m_thresh;    //�ж�Ϊ��ѡ�����ֵ

		void detectCandidatePoints(const cv::Mat &)override;    //���õ���ѡ��
		void filterKeyPoints(const cv::Mat &)override;          //�ɺ�ѡ����˵õ�������

		/*
		* �жϸ����ĵ��Ƿ�Ϊ��������Ȥֵ���ĵ㣬(c, r)Ϊ�������Ͻ�����
		*/
		bool isPointInBlock(const KeyPoint &, const int &c, const int &r)const;
	};
}
#endif
