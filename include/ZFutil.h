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
    tuple<cv::Mat, cv::Mat, cv::Mat> cropResizeRotate(cv::Mat &channelwise_avg, vector<cv::Point2f> &initlandmark_0, vector<cv::Point2f> &initlandmarks_1);
    int loadImg(const char *txtFilePath, cv::Mat &img);
    int load_initlandmark(const char *filepath, vector<cv::Point2f> &initlandmark_0);
}
#endif //PB_ZFUTIL_H
