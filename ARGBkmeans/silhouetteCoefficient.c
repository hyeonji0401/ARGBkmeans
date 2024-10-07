#include"silhouette.h"

double* silhouetteCoefficient(double** data, int* labels, double** centers, int n, int k, int dim) {
    double* silhouetteScores = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        double a = 0.0;  // 같은 클러스터 내 평균 거리
        double b = DBL_MAX;  // 다른 클러스터와의 최소 평균 거리

        int clusterSize = 0;
        for (int j = 0; j < n; j++) {
            if (labels[i] == labels[j]) {
                clusterSize++;
            }
        }

        //클러스터 크기가 1인 경우, 실루엣 계수를 0으로 설정
        if (clusterSize == 1) {
            silhouetteScores[i] = 0.0;
            continue;
        }

        //a(i) 계산: 같은 클러스터 내의 평균 거리
        for (int j = 0; j < n; j++) {
            if (labels[i] == labels[j]) {
                a += euclideanDistance(data[i], data[j], dim);
            }
        }
        if (clusterSize > 1) {
            a /= (clusterSize - 1);  // 자기 자신을 제외하고 평균 거리 계산
        }

        //b(i) 계산: 가장 가까운 다른 클러스터와의 평균 거리
        for (int c = 0; c < k; c++) {
            if (c == labels[i]) continue;  // 현재 클러스터는 제외
            double otherClusterDist = 0.0;
            int otherClusterSize = 0;

            for (int j = 0; j < n; j++) {
                if (labels[j] == c) {
                    otherClusterDist += euclideanDistance(data[i], data[j], dim);
                    otherClusterSize++;
                }
            }

            if (otherClusterSize > 0) {
                otherClusterDist /= otherClusterSize;
                if (otherClusterDist < b) {
                    b = otherClusterDist;
                }
            }
        }

        //Silhouette 값 계산
        silhouetteScores[i] = (b - a) / fmax(a, b);
    }

    return silhouetteScores;
}

