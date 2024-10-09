#include"findCenter.h"

// 중심점 변화 여부 확인 함수
int isCenterChanged(double** oldCenters, double** newCenters, int dim, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dim; j++) {
            if (fabs(oldCenters[i][j] - newCenters[i][j]) > 1e-6) {
                return 1;
            }
        }
    }
    return 0;
}