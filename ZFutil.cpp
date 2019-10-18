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

        cv::Mat T = (cv::Mat_<float>(2, 2) << a, -b, b, a);

        // convert Point2f to cv::Mat
        cv::Mat srcMean_mat = (cv::Mat_<float>(1, 2) << srcMean.x, srcMean.y);

        srcMean_mat = srcMean_mat * T;
        cv::Mat destMean_mat = (cv::Mat_<float>(1, 2) << destMean.x, destMean.y);

        return pair<cv::Mat, cv::Mat>(T, destMean_mat - srcMean_mat);

    }


    tuple<cv::Mat, cv::Mat, cv::Mat> cropResizeRotate(cv::Mat &channelwise_avg, vector<cv::Point2f> &initlandmark_0,
                          vector<cv::Point2f> &initlandmarks_1) {
        auto pair = bestFit(initlandmark_0, initlandmarks_1); // use structured binding to unpack
        cv::Mat A = pair.first;
        cv::Mat t = pair.second;
        cv::Mat A2 = A.inv();
        cv::Mat t2 = -t * A2;

        cv::Mat outImg = cv::Mat::zeros(channelwise_avg.rows, channelwise_avg.cols, channelwise_avg.type());
        cv::Mat tmp(2, 1, CV_32FC1);
        cout << t2 << endl;
        cout << t2.at<float>(0,1) << endl;
        cout << t2.at<float>(0,0) << endl;
        tmp.at<float>(0,0) = t2.at<float>(0, 1);
        tmp.at<float>(1,0) = t2.at<float>(0, 0);
        cout << tmp << endl;
        cv::Mat M;
        cv::hconcat(A2, tmp, M);
        cout << A2 << endl;
        cout << tmp << endl;
        cout << M << endl;
        cv::warpAffine(channelwise_avg, outImg, M, outImg.size());
        return tuple<cv::Mat, cv::Mat, cv::Mat>{outImg, A, t};
    }


}

