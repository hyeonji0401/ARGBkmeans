#include"kmeans.h"

// 데이터 할당 함수 (유클리디안 거리 기준으로 할당)
void assignCluster(double** data, double** centers, int* labels, int n, int dim, int k) {
    for (int i = 0; i < n; i++) {
        double minDist = DBL_MAX;
        int cluster = -1;
        for (int j = 0; j < k; j++) {
            double dist = euclideanDistance(data[i], centers[j], dim);
            if (dist < minDist) {
                minDist = dist;
                cluster = j;
            }
        }
        labels[i] = cluster;
    }
}