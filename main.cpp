#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/framework/tensor.h"
#include "opencv2/opencv.hpp"
#include "detectFace.h"
#include "imiCV.h"
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include <utility>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ZFutil.h"

//using namespace cv;
using namespace std;
using namespace tensorflow;

int main(int argc, char *argv[]) {
    // read video
    string video_path{"../self_video3.mp4"};
    cv::VideoCapture cap{video_path};

    if (!cap.isOpened()) {
        cout << "failed to open video " << video_path << endl;
        return -1;
    }

    // get video properties
    cout << "frame width: " << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
    cout << "frame height: " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "fps: " << cap.get(CV_CAP_PROP_FPS) << endl;

    // create session and load model
    string model_path = "../Model_pb/frozen_model.pb"; // path relative to the actual executable, not source file
//        string input_tensor_name="conv2d_1_input";     //input_tensor_name
//        string output_tensor_name="Stage1/Reshape_1";
    Session *session;
    Status status = NewSession(SessionOptions(), &session);
    if (!status.ok()) {
        cout << "Could not create Tensorflow session." + status.ToString() << endl;
        return -1;
    }
    cout << "successfully create Tensorflow session." << endl;
    GraphDef graphdef; //Graph Definition for current model
    Status status_load = ReadBinaryProto(Env::Default(), model_path, &graphdef); //从pb文件中读取图模型;
    if (!status_load.ok()) {
        cout << "Error reading graph definition: " + status_load.ToString() << endl;
        return -1;
    }
    Status status_create = session->Create(graphdef); //将模型导入会话Session中;
    if (!status_create.ok()) {
        cout << "Error loading graph into session: " + status.ToString() << endl;
        return -1;
    }
    cout << "graph successfully loaded into session.\n";

    // initialize face detector
    imi::FaceDetectionInitialization();

    // load initlandmarks_0
    fstream fs;
    fs.open("../initlandmarks_0.txt", ios::in);
    if (!fs) {
        printf("failed to open initlandmarks_0.txt");
        return -1;
    }
    string line;
    double x;
    double y;
    vector<cv::Point2f> initlandmark_0{};
    while (getline(fs, line)) {
        auto tmp = line.find(',');
        x = std::stod(line.substr(0, tmp));
        y = std::stod(line.substr(tmp + 1));
        initlandmark_0.emplace_back(x, y);
    }
    fs.close();

    bool reset = true;

    // read frames
    cv::Mat img;
    while (true) {
        cap >> img;

        if (img.empty()) {
            break;
        }

        // compute channel-wise average
        vector<cv::Mat> channels;
        cv::split(img, channels);
        cv::Mat channelwise_avg(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
        for (auto i = 0; i < img.channels(); i++) {
            channelwise_avg += channels[i];
        }
        channelwise_avg /= img.channels();

//        printf("%d\n", channels[0].at<uchar>(0, 0));
//        printf("%d\n", channels[1].at<uchar>(0, 0));
//        printf("%d\n", channels[2].at<uchar>(0, 0));
//        printf("%d\n", channelwise_avg.at<uchar>(0, 0));

        if (reset) {
            int startX0{0};
            int startY0{0};
            int endX0{0};
            int endY0{0};
            int h = img.rows;
            int w = img.cols;

            // perform face detection
            imi::imiMat imi_img(img.rows, img.cols, IMI_CV_8UC3, img.data);
            vector<imi::FaceInfo> results = imi::detectFace(&imi_img);
            if (results.empty()) {
                printf("no face detected\n");
            } else {
                // draw bbox on img
                // cv::rectangle(img, cv::Rect(results[0].bbox.x, results[0].bbox.y, results[0].bbox.width, results[0].bbox.height), cv::Scalar(255, 0, 0));
                cv::Rect bbox(results[0].bbox.x, results[0].bbox.y, results[0].bbox.width, results[0].bbox.height);
                auto initlandmarks_1 = ZF::bestFitRect(initlandmark_0, bbox);
                //
                //auto tmp = ZF::cropResizeRotate(channelwise_avg, initlandmarks_1);
            }

            // show img
            cv::imshow("img", img);
            cv::waitKey(5);

            break;
        }

    }

    cap.release();

    /*vector<pair<string, Tensor>> feeddict = {{},
                                             {}};

    vector<tensorflow::Tensor> outputs;
    string output_node = output_tensor_name;
    Status status_run = session->Run({{input_tensor_name, resized_tensor}}, {output_node}, {}, &outputs);

    if (!status_run.ok()) {
        cout << "ERROR: RUN failed..." << std::endl;
        cout << status_run.ToString() << "\n";
        return -1;
    }*/

    return 0;
}
