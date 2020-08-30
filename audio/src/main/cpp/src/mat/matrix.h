//
// Created by 周秀敏 on 2020/8/29.
//

#ifndef CPPLEARN_MATRIX_H
#define CPPLEARN_MATRIX_H
#include <android/log.h>
#include <vector>

#define TAG "MAT"

#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)


namespace mat{
    void randMatrix(std::vector<std::vector<float>> &matrix);

    std::vector<std::vector<float>>
    multiplyMatrixByBlas(std::vector<std::vector<float>> &matrixA, std::vector<std::vector<float>> &matrixB);

    std::vector<std::vector<float>>
    multiplyMatrixNormal(std::vector<std::vector<float>> &matrixA, std::vector<std::vector<float>> &matrixB);

    std::vector<std::vector<float>>
    multiplyMatrixAdvance(std::vector<std::vector<float>> &matrixA, std::vector<std::vector<float>> &matrixB);

    bool verifyTwoMatrixAreEqual(std::vector<std::vector<float>> &matrixA, std::vector<std::vector<float>> &matrixB);

    void test();

}

#endif //CPPLEARN_MATRIX_H
