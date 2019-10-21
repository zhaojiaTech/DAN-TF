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

    // load initlandmark_0
    vector<cv::Point2f> initlandmark_0;
    ZF::load_initlandmark("../initlandmarks_0.txt", initlandmark_0);

    // load meanImg
    cv::Mat meanImg;
    ZF::loadImg("../meanImg.txt", meanImg);

    // load stdDevImg
    cv::Mat stdDevImg;
    ZF::loadImg("../stdDevImg.txt", stdDevImg);

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
                auto tuple= ZF::cropResizeRotate(channelwise_avg, initlandmark_0, initlandmarks_1);
                cv::Mat &inputImg = get<0>(tuple);
                inputImg.convertTo(inputImg, CV_32FC1);
//                cout << inputImg.type() << endl;
//                cout << meanImg.type() << endl;
                cv::Mat &A = get<1>(tuple);
                cv::Mat &t = get<2>(tuple);
                inputImg -= meanImg;
                inputImg /= stdDevImg;

                // convert inputImg to tensor
                Tensor inputImg_tensor(DT_FLOAT, TensorShape({1, 112, 112, 1}));
                auto input_tensor_mapped = inputImg_tensor.tensor<float, 4>();
                for(int i = 0; i < inputImg.rows; i++){
                    for(int j = 0; j < inputImg.cols; j++){
                        input_tensor_mapped(0, i, j, 0) = inputImg.at<float>(i, j);
                    }
                }
                // convert bool to tensor
                Tensor isTrain_tensor(DT_BOOL, TensorShape());
                isTrain_tensor.scalar<bool>()() = false;
                vector<pair<string, Tensor>> feedDict = {{"Placeholder", inputImg_tensor},
                                                         {"Placeholder_2", isTrain_tensor}};

                vector<tensorflow::Tensor> outputs;
                string output_node = "Stage1/Reshape_1";
                Status status_run = session->Run(feedDict, {output_node}, {}, &outputs);

                if (!status_run.ok()) {
                    cout << "ERROR: RUN failed..." << std::endl;
                    cout << status_run.ToString() << "\n";
                    return -1;
                }

                cout << outputs[0].shape().dim_size(0) << endl; // 1
                cout << outputs[0].shape().dim_size(1) << endl; // 106
                cout << outputs[0].shape().dim_size(2) << endl; // 2

                cv::Mat landmark_out = cv::Mat::zeros(112, 2, CV_32FC1);
                for(int i = 0; i < 112; i++){
                    landmark_out.at<float>(i, 0) = outputs[0].tensor<float_t, 3>()(0, i, 0) - t.at<float>(0,0);
                    landmark_out.at<float>(i, 1) = outputs[0].tensor<float_t, 3>()(0, i, 1) - t.at<float>(0,1);
                }

                landmark_out = landmark_out * A.inv();
//                cout << landmark_out << endl;
                cout << A << endl;
                cout << t << endl;
                landmark_out.convertTo(landmark_out, CV_8UC1);
//                cout << landmark_out << endl;
                for(int i = 0; i < landmark_out.rows; i++ ){
//                    cout << cv::Point2f(landmark_out.at<int>(i, 0), landmark_out.at<int>(i, 1)) << endl;
                    cv::circle(img, cv::Point2f(landmark_out.at<int>(i, 0), landmark_out.at<int>(i, 1)), 2, cv::Scalar(0, 0, 255));
                }


            }

            // show img
            cv::imshow("img", img);
            cv::waitKey(5);
            reset = false;
            break;
        }

    }

    cap.release();


    return 0;
}
