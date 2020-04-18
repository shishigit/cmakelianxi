// A simple program that computes the square root of a number
#include <cmath>
#include <iostream>
#include <string>

#include "TutorialConfig.h"

// 使用动态编译
#ifdef USE_MYMATH

#  include "MathFunctions.h"

#endif

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                  << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // 系统函数检测
#if defined(DINGJI_HAVE_LOG)
    std::cout << "顶级函数检测：DINGJI_HAVE_LOG" << std::endl;
#endif
#if defined(DINGJI_HAVE_EXPX)
    std::cout << "顶级函数检测：DINGJI_HAVE_EXPX"  << std::endl;
#endif
    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // 使用动态编译
#ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif

    std::cout << "The square root of " << inputValue
              << " is " << outputValue
              << std::endl;
    return 0;
}
