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

    pair<vector<double>, vector<double>> bestFitRect(const vector<double> &initlandmark_xs, const vector<double> &initlandmark_ys, const vector<int> &&bbox){
        int boxcenter_x = (bbox[0] + bbox[2]) / 2;
        int boxcenter_y = (bbox[1] + bbox[3]) / 2;
        int box_width{bbox[2] - bbox[0]};
        int box_height{bbox[3] - bbox[1]};
        double meanShapeWidth = *max_element(initlandmark_xs.begin(), initlandmark_xs.end()) - *min_element(initlandmark_xs.begin(), initlandmark_xs.end());
        double meanShapeHeight = *max_element(initlandmark_ys.begin(), initlandmark_ys.end()) - *min_element(initlandmark_ys.begin(), initlandmark_ys.end());
        double scaleWidth = box_width / meanShapeWidth;
        double scaleHeight = box_height / meanShapeHeight;
        double scale = (scaleWidth + scaleHeight) / 2;
        vector<double> S0_xs{};
        vector<double> S0_ys{};
        for(int i = 0; i < initlandmark_xs.size(); i++){
            S0_xs.push_back(scale * initlandmark_xs[i]);
            S0_ys.push_back(scale * initlandmark_ys[i]);
        }
        double S0_center_x = (*min_element(S0_xs.begin(), S0_xs.end()) + *max_element(S0_xs.begin(), S0_xs.end())) / 2;
        double S0_center_y = (*min_element(S0_ys.begin(), S0_ys.end()) + *max_element(S0_ys.begin(), S0_ys.end())) / 2;
        for(int i = 0; i < initlandmark_xs.size(); i++){
            S0_xs[i] += boxcenter_x - S0_center_x;
            S0_ys[i] += boxcenter_y - S0_center_y;
        }
        return pair<vector<double>, vector<double>>(S0_xs, S0_ys);
    }


    void bestFit(){

    }


    void cropResizeRotate(cv::Mat &img, pair<vector<double>, vector<double>> &initlandmarks_1){

    }


}

