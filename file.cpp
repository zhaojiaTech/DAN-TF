#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/framework/tensor.h"
#include "detectFace.h"
#include "imiCV.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;
using namespace tensorflow;
using namespace imi;

int main(){
    ifstream ifs;
    ifs.open("../meanImg.txt", ios::in);
    cv::Mat meanImg = Mat::zeros(112, 112, CV_32FC1);
    string line;
    int row{0};
    int col{0};
    while(row < 112 && getline(ifs, line)){
        istringstream iss(line);
        float value;
        while(col < 112 && iss >> value){
            meanImg.at<float>(row, col) = value;
            col++;
        }
        col = 0;
        row++;
    }

	ifs.close();


//    cout << meanImg << endl;
    cv::Mat tmp;
    meanImg.convertTo(tmp, CV_8UC1);
    cv::imshow("meanImg", tmp);
    cv::waitKey(0);
//    cout << meanImg.size() << endl;
    /*for (int i = 0; i < 112; i++)
	{
        uchar *pixelPtr = mean_Img.ptr<uchar>(i);
		for (int j = 0; j < 112; j++)
		{
            
			cout<< pixelPtr[j];
		}
	}*/
    /*imshow("meanImg",mean_Img);
    waitKey(0);*/
    return 0;
}

	


