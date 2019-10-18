//
// Created by zjtech on 2019/10/17.
//
#include <vector>
#include <algorithm>
#include <utility>
#include "opencv2/opencv.hpp"
#include "ZFutil.h"

using namespace std;

namespace ZF{

    vector<cv::Point2f> bestFitRect(const vector<cv::Point2f> &initlandmark_0, const cv::Rect &bbox){

        cv::Point2f boxcenter(bbox.x + bbox.width/2, bbox.y + bbox.height/2);
        cv::Rect meanS_box = cv::boundingRect(initlandmark_0);

        double scaleWidth = bbox.width / meanS_box.width;
        double scaleHeight = bbox.height / meanS_box.height;
        double scale = (scaleWidth + scaleHeight) / 2;

        vector<cv::Point2f> result;
        for(int i = 0; i < initlandmark_0.size(); i++){
            result.emplace_back(initlandmark_0[i].x * scale, initlandmark_0[i].y * scale);
        }

        cv::Rect result_bbox = cv::boundingRect(result);
        cv::Point2f result_boxcenter(result_bbox.x + result_bbox.width/2, result_bbox.y + result_bbox.height/2);

        for (int i = 0; i < result.size(); i++) {
            result[i].x += boxcenter.x - result_boxcenter.x;
            result[i].y += boxcenter.y - result_boxcenter.y;
        }

        return result;
    }


    void bestFit(){

    }


    void cropResizeRotate(cv::Mat &channelwise_avg, pair<vector<double>, vector<double>> &initlandmarks_1){
        bestFit();
    }


}

