#ifndef peoplehead_HPP
#define peoplehead_HPP

#include "../common/algorithm_base.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>
#include <string>

class peoplehead : public AlgorithmBase {
public:
    void detect(cv::Mat input_image) override;
    void init(std::string model_path) override;  
    void release() override;  

private:
    class impl;
    std::unique_ptr<impl> impl_;
};

#endif // peoplehead_HPP
