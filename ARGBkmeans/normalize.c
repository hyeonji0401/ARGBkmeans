#include "normalize.h"
#define COLS 4
void normalize(double **data, int rows, int cols) {
    double min_val[COLS], max_val[COLS];

    // 초기화
    for (int j = 0; j < cols; j++) {
        min_val[j] = DBL_MAX;
        max_val[j] = -DBL_MAX;
    }

    // 각 열의 최소값과 최대값 계산
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] < min_val[j]) {
                min_val[j] = data[i][j];
            }
            if (data[i][j] > max_val[j]) {
                max_val[j] = data[i][j];
            }
        }
    }

    // 정규화 수행
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (max_val[j] != min_val[j]) {
                data[i][j] = (data[i][j] - min_val[j]) / (max_val[j] - min_val[j]);
            }
            else {
                data[i][j] = 0.0; // 최대값과 최소값이 같으면 0으로 설정
            }
        }
    }
}