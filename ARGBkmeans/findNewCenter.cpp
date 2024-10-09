#include"findCenter.h"

// 새로운 중심점 계산 함수
void findNewCenter(double** data, double** centers, int* labels, int n, int dim, int k) {
    int* count = (int*)calloc(k, sizeof(int));
    double** newCenters = (double**)malloc(k * sizeof(double*));
    for (int i = 0; i < k; i++) {
        newCenters[i] = (double*)calloc(dim, sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        int cluster = labels[i];
        count[cluster]++;
        for (int j = 0; j < dim; j++) {
            newCenters[cluster][j] += data[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dim; j++) {
            if (count[i] > 0) {
                centers[i][j] = newCenters[i][j] / count[i];
            }
        }
        free(newCenters[i]);
    }

    free(newCenters);
    free(count);
}