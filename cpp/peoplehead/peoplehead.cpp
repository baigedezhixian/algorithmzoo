#include "peoplehead.hpp"
#include <iostream>
#include <string>
#include "../common/RKNN2Wrapper/rknn2_wrapper.hpp"
#include "../common/YoloFamily/Yolo_wrapper.hpp"

class peoplehead::impl
{
public:
    impl(std::string model_path) {
        std::vector<std::string> phai;
        peoplehead_detect = std::make_shared<rknnwrapper::rknn_wrapper>(phai, model_path + "/head.rknn", 0);
        yolov8_instance = std::make_shared<Yolov8<rknnwrapper::rknn_wrapper>>(1280, 736, peoplehead_detect);
    }

    void detect(cv::Mat input_image) {
        float con_thres = 0.5;
        float nms_thres = 0.6;
        auto peoplehead_objects = yolov8_instance->get_objects(input_image, con_thres, nms_thres);

        cv::Mat draw_pic = input_image.clone();
        std::cout << "peoplehead_object:";
        for (const auto& peoplehead_object : peoplehead_objects) {
            cv::rectangle(draw_pic, cv::Point(peoplehead_object.x1, peoplehead_object.y1), cv::Point(peoplehead_object.x2, peoplehead_object.y2), cv::Scalar(0, 0, 255), 2);
        }

        if (!peoplehead_objects.empty()) {
            cv::imwrite(std::to_string(peoplehead_objects[0].x1) + std::to_string(peoplehead_objects[0].y1) + std::to_string(peoplehead_objects[0].x2) + ".jpg", draw_pic);
        }
    }

private:
    std::shared_ptr<rknnwrapper::rknn_wrapper> peoplehead_detect;
    std::shared_ptr<Yolov8<rknnwrapper::rknn_wrapper>> yolov8_instance;
};

// peoplehead::peoplehead(std::string model_path) : impl_(std::make_unique<impl>(model_path)) {}

void peoplehead::detect(cv::Mat input_image) {
    std::cout << "peoplehead detection" << std::endl;
    if (impl_) {
        impl_->detect(input_image);
    } else {
        std::cerr << "Error: impl_ not initialized!" << std::endl;
    }
}

void peoplehead::init(std::string model_path) {
    impl_ = std::make_unique<impl>(model_path);
}

void peoplehead::release() {
    impl_.reset();
}


extern "C" AlgorithmBase* create() {
    std::cout << "create peoplehead\n";
    return new peoplehead();
}
