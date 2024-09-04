#include "body.hpp"
#include <iostream>
#include <string>
#include "../common/RKNN2Wrapper/rknn2_wrapper.hpp"
#include "../common/YoloFamily/Yolo_wrapper.hpp"
#include "../common/Primitives/tensor_conversions.hpp"

class body::impl
{
public:
    impl(std::string model_path) {
        std::vector<std::string> phai;
        body_detect = std::make_shared<rknnwrapper::rknn_wrapper>(phai, model_path + "/pedestrian.rknn", 0);
        yolov8_instance = std::make_shared<Yolov8<rknnwrapper::rknn_wrapper>>(1280, 736, body_detect);
    }

    void detect(cv::Mat input_image) {
        float con_thres = 0.1;
        float nms_thres = 0.6;

        auto copyinput_image = input_image.clone();

        cv::resize(copyinput_image, copyinput_image ,cv::Size(1280,736));

        auto result = body_detect->forward(copyinput_image.data, { 1, copyinput_image.rows, copyinput_image.cols,copyinput_image.channels() }, RKNN_TENSOR_NHWC);

        std::cout<<"dsddddqqq\n";
        
        auto body_objects = yolov8_instance->get_objects(input_image, con_thres, nms_thres);

        cv::Mat draw_pic = input_image.clone();
        std::cout << "body_object:";
        for (const auto& body_object : body_objects) {
            cv::rectangle(draw_pic, cv::Point(body_object.x1, body_object.y1), cv::Point(body_object.x2, body_object.y2), cv::Scalar(0, 0, 255), 2);
        }

        if (!body_objects.empty()) {
            cv::imwrite(std::to_string(body_objects[0].x1) + std::to_string(body_objects[0].y1) + std::to_string(body_objects[0].x2) + ".jpg", draw_pic);
        }
    }

private:
    std::shared_ptr<rknnwrapper::rknn_wrapper> body_detect;
    std::shared_ptr<Yolov8<rknnwrapper::rknn_wrapper>> yolov8_instance;
};

// body::body(std::string model_path) : impl_(std::make_unique<impl>(model_path)) {}

void body::detect(cv::Mat input_image) {
    std::cout << "body detection" << std::endl;
    if (impl_) {
        impl_->detect(input_image);
    } else {
        std::cerr << "Error: impl_ not initialized!" << std::endl;
    }
}

void body::init(std::string model_path) {
    impl_ = std::make_unique<impl>(model_path);
}

void body::release() {
    impl_.reset();
}

body::body() 
{}

extern "C" AlgorithmBase* create() {
    std::cout << "create body\n";
    return new body();
}
