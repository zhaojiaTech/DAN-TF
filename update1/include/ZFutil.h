//
// Created by zjtech on 2019/10/17.
//

#ifndef PB_ZFUTIL_H
#define PB_ZFUTIL_H

#include <vector>
#include <utility>

using namespace std;

namespace ZF{
    pair<vector<double>, vector<double>> bestFitRect(const vector<double> &initlandmark_xs, const vector<double> &initlandmark_ys, const vector<int> &&bbox);
}
#endif //PB_ZFUTIL_H
