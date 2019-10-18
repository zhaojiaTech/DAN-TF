//
// Created by zjtech on 2019/10/17.
//
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "opencv2/opencv.hpp"
#include "ZFutil.h"

using namespace std;

namespace ZF {

    vector<cv::Point2f> bestFitRect(const vector<cv::Point2f> &initlandmark_0, const cv::Rect &bbox) {

        cv::Point2f boxcenter(bbox.x + bbox.width / 2, bbox.y + bbox.height / 2);
        cv::Rect meanS_box = cv::boundingRect(initlandmark_0);

        double scaleWidth = bbox.width / meanS_box.width;
        double scaleHeight = bbox.height / meanS_box.height;
        double scale = (scaleWidth + scaleHeight) / 2;

        vector<cv::Point2f> result;
        for (int i = 0; i < initlandmark_0.size(); i++) {
            result.emplace_back(initlandmark_0[i].x * scale, initlandmark_0[i].y * scale);
        }

        cv::Rect result_bbox = cv::boundingRect(result);
        cv::Point2f result_boxcenter(result_bbox.x + result_bbox.width / 2, result_bbox.y + result_bbox.height / 2);

        for (int i = 0; i < result.size(); i++) {
            result[i].x += boxcenter.x - result_boxcenter.x;
            result[i].y += boxcenter.y - result_boxcenter.y;
        }

        return result;
    }


    pair<cv::Mat, cv::Mat> bestFit(vector<cv::Point2f> &dest, vector<cv::Point2f> &src) {
        cv::Point2f destMean{0, 0};
        for (const auto point : dest) {
            destMean += point;
        }
        destMean *= 1.0f / dest.size();

        cv::Point2f srcMean{0, 0};
        for (const auto point : src) {
            srcMean += point;
        }
        srcMean *= 1.0f / src.size();

        vector<float> srcVec;
        for (const auto point : src) {
            srcVec.push_back((point - srcMean).x);
            srcVec.push_back((point - srcMean).y);
        }

        vector<float> destVec;
        for (const auto point : dest) {
            destVec.push_back((point - destMean).x);
            destVec.push_back((point - destMean).y);
        }

        // convert std::vector to cv::Mat
        cv::Mat srcMat(srcVec.size(), 1, CV_32FC1, (float*)srcVec.data()); // (212, 1)
        cv::Mat destMat(destVec.size(), 1, CV_32FC1, (float*)destVec.data()); // (212, 1)

        double srcNorm{cv::norm(srcMat, cv::NORM_L2)};
        double a{srcMat.dot(destMat) / pow(srcNorm, 2)};
        double b{0};
        for (int i = 0; i < dest.size(); i++) {
            b += srcVec[2 * i] * destVec[2 * i + 1] - srcVec[2 * i + 1] * destVec[2 * i];
        }
        b /= pow(srcNorm, 2);

        cv::Mat T = (cv::Mat_<double>(2, 2) << a, -b, b, a);
        cout << T << endl;

        // convert Point2f to cv::Mat
        cv::Mat srcMean_mat = (cv::Mat_<double>(1, 2) << srcMean.x, srcMean.y);

        srcMean_mat = srcMean_mat * T;
        cv::Mat destMean_mat = (cv::Mat_<double>(1, 2) << destMean.x, destMean.y);


        return pair<cv::Mat, cv::Mat>(T, destMean_mat - srcMean_mat);

    }


    int cropResizeRotate(cv::Mat &channelwise_avg, vector<cv::Point2f> &initlandmark_0,
                          vector<cv::Point2f> &initlandmarks_1) {
        bestFit(initlandmark_0, initlandmarks_1);
        return 0;
    }


}

