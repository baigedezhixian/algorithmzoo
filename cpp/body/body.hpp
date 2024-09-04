#ifndef body_HPP
#define body_HPP

#include "../common/algorithm_base.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>
#include <string>

class body : public AlgorithmBase {
public:
    body();
    void detect(cv::Mat input_image) override;
    void init(std::string model_path) override;  
    void release() override;  

private:
    class impl;
    std::unique_ptr<impl> impl_;
};

#endif // body_HPP
