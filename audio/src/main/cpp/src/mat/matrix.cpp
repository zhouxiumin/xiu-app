//
// Created by 周秀敏 on 2020/8/29.
//

#include "matrix.h"
#include <iostream>
#include <ctime>
#include <random>
#include <cblas.h>

namespace mat {

    void test() {
        using namespace std;
        clock_t startTime, endTime;
        startTime = clock();
        // A 1000 * 2000  B 2000 * 500
//        const int n = 3;
//        const int k = 4;
//        const int m = 5;

//        const int n = 800;
//        const int k = 1000;
//        const int m = 500;
        const int n = 100;
        const int k = 800;
        const int m = 500;

        vector<vector<float>> matrixA(n);
        for (int i = 0; i < n; ++i) {
            matrixA[i].resize(k);
        }
        vector<vector<float>> matrixB(k);
        for (int i = 0; i < k; ++i) {
            matrixB[i].resize(m);
        }
        randMatrix(matrixA);
        randMatrix(matrixB);
        endTime = clock();
        LOGI("The run time of generate matrix is: %fs", (double) (endTime - startTime) / CLOCKS_PER_SEC);

        startTime = clock();
        vector<vector<float>> matrixE = multiplyMatrixByBlas(matrixA, matrixB);
        endTime = clock();
        LOGI("The run time of openBLAS matrix multiply is: %fs", (double) (endTime - startTime) / CLOCKS_PER_SEC);

        startTime = clock();
        vector<vector<float>> matrixC = multiplyMatrixNormal(matrixA, matrixB);
        endTime = clock();
        LOGI("The run time of Normal matrix multiply is: %fs", (double) (endTime - startTime) / CLOCKS_PER_SEC);

        startTime = clock();
        vector<vector<float>> matrixD = multiplyMatrixAdvance(matrixA, matrixB);
        endTime = clock();
        LOGI("The run time of Advance matrix multiply is: %fs", (double) (endTime - startTime) / CLOCKS_PER_SEC);

        bool flag = verifyTwoMatrixAreEqual(matrixC, matrixD);
        LOGI("The result(C D) of multiply on A, B is equal?: %d", flag);

        flag = verifyTwoMatrixAreEqual(matrixC, matrixE);
        LOGI("The result(C E) of multiply on A, B is equal?: %d", flag);
    }

    void randMatrix(std::vector<std::vector<float>> &matrix) {
        using namespace std;
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 10.0);
        for (int i = 0; i < matrix.size(); ++i) {
            vector<float> rows = matrix[i];
            for (int j = 0; j < rows.size(); ++j) {
                matrix[i][j] = dis(gen);
            }
        }
    }

    std::vector<std::vector<float>>
    multiplyMatrixNormal(std::vector<std::vector<float>> &matrixA,
                         std::vector<std::vector<float>> &matrixB) {
        using namespace std;
        int n = matrixA.size();
        int k = matrixB.size();
        int m = matrixB[0].size();
        if (matrixA[0].size() != k) {
            return std::vector<std::vector<float>>();
        }
        vector<vector<float>> matrixC(n);
        for (int i = 0; i < n; ++i) {
            matrixC[i].resize(m);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int p = 0; p < k; ++p) {
                    matrixC[i][j] += matrixA[i][p] * matrixB[p][j];
                }
            }
        }
        return matrixC;
    }

    std::vector<std::vector<float>>
    multiplyMatrixAdvance(std::vector<std::vector<float>> &matrixA,
                          std::vector<std::vector<float>> &matrixB) {
        using namespace std;
        int n = matrixA.size();
        int k = matrixB.size();
        int m = matrixB[0].size();
        if (matrixA[0].size() != k) {
            return std::vector<std::vector<float>>();
        }
        vector<vector<float>> matrixC(n);
        for (int i = 0; i < n; ++i) {
            matrixC[i].resize(m);
        }

        for (int p = 0; p < k; ++p) {
            for (int i = 0; i < n; ++i) {
                float r = matrixA[i][p];
                for (int j = 0; j < m; ++j) {
                    matrixC[i][j] += r * matrixB[p][j];
                }
            }
        }
        return matrixC;
    }

    bool verifyTwoMatrixAreEqual(std::vector<std::vector<float>> &matrixA,
                                 std::vector<std::vector<float>> &matrixB) {
        int n = matrixA.size();
        int m = matrixA[0].size();
        const float e = 1e-1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                float fa = matrixA[i][j];
                float fb = matrixB[i][j];
                if (abs(fa - fb) > e) {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<std::vector<float>>
    multiplyMatrixByBlas(std::vector<std::vector<float>> &matrixA,
                         std::vector<std::vector<float>> &matrixB) {
        using namespace std;
        int n = matrixA.size();
        int k = matrixB.size();
        int m = matrixB[0].size();
        if (matrixA[0].size() != k) {
            return std::vector<std::vector<float>>();
        }
        vector<vector<float>> matrixC(n);
        for (int i = 0; i < n; ++i) {
            matrixC[i].resize(m);
        }
        const enum CBLAS_ORDER Order = CblasRowMajor;
        const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
        const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
        const float alpha = 1;
        const float beta = 0;
        const int lda = k;//A的列
        const int ldb = m;//B的列
        const int ldc = m;//C的列
        float A[n * k];
        float B[k * m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                A[k * i + j] = matrixA[i][j];
            }
        }
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < m; ++j) {
                B[m * i + j] = matrixB[i][j];
            }
        }
        float C[n * m];
        cblas_sgemm(Order, TransA, TransB, n, m, k, alpha, A, lda, B, ldb, beta, C, ldc);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrixC[i][j] = C[m * i + j];
            }
        }
        return matrixC;
    }

}
