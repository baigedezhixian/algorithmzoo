// algorithm_base.hpp
#ifndef ALGORITHM_BASE_HPP
#define ALGORITHM_BASE_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class AlgorithmBase {
public:
    virtual ~AlgorithmBase() = default;
    virtual void detect(cv::Mat input_image) = 0;
    virtual void init(std::string model_path) = 0;
    virtual void release() = 0;
};

#endif // ALGORITHM_BASE_HPP
