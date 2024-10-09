#include"euclidean.h"

// 유클리디안 거리 계산 함수
double euclideanDistance(double* a, double* b, int dim) {
    double sum = 0.0;
    for (int i = 0; i < dim; i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}