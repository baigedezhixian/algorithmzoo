// main.cpp
#include <iostream>
#include <dlfcn.h>
#include "../cpp/common//algorithm_base.hpp"
#include <opencv2/opencv.hpp>

int main() {
    void* handle1 = dlopen("libbody.so", RTLD_LAZY);
    if (!handle1) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    // void* handle2 = dlopen("libpeoplehead.so", RTLD_LAZY);
    // if (!handle2) {
    //     std::cerr << "Cannot open library: " << dlerror() << '\n';
    //     return 1;
    // }

    // Load the symbols
    typedef AlgorithmBase* create_t();
    create_t* create_module1 = (create_t*) dlsym(handle1, "create");
    // create_t* create_module2 = (create_t*) dlsym(handle2, "create");

    if (!create_module1 ) {
        std::cerr << "Cannot load symbol: " << dlerror() << '\n';
        return 1;
    }

    // Create instances
     std::cout<<"dsds\n";
    AlgorithmBase* module1 = create_module1();
    std::cout<<"dsdsd\n";
    // AlgorithmBase* module2 = create_module2();
    module1->init("/home/glasssix/cw/module_test/safemodels");

    auto img = cv::imread("/home/glasssix/cw/module_test/image/panpa.jpg");
    // Use the instances
    module1->detect(img);
    // module2->detect();

    // Cleanup
    delete module1;
    // delete module2;

    dlclose(handle1);
    // dlclose(handle2);

    return 0;
}
