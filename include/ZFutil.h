//
// Created by zjtech on 2019/10/17.
//

#ifndef PB_ZFUTIL_H
#define PB_ZFUTIL_H

#include <vector>
#include <utility>

using namespace std;

namespace ZF{
    vector<cv::Point2f> bestFitRect(const vector<cv::Point2f> &initlandmark_0, const cv::Rect &bbox);
    pair<cv::Mat, cv::Mat> bestFit(vector<cv::Point2f> &dest, vector<cv::Point2f> &src);
}
#endif //PB_ZFUTIL_H
