#include "silhouette.h"

// 각 클러스터의 평균 실루엣 계수와 편차를 계산하는 함수
void evaluateSilhouette(double* silhouetteScores, int* labels, int n, int k) {
    double* clusterSilhouetteSum = (double*)calloc(k, sizeof(double));
    double* clusterSilhouetteSquaredSum = (double*)calloc(k, sizeof(double));
    int* clusterSizes = (int*)calloc(k, sizeof(int));

    // 각 클러스터별 실루엣 계수 합계 및 크기 계산
    for (int i = 0; i < n; i++) {
        int cluster = labels[i];
        clusterSilhouetteSum[cluster] += silhouetteScores[i]; //각 클러스터 실루엣 계수 총 합
        clusterSilhouetteSquaredSum[cluster] += silhouetteScores[i] * silhouetteScores[i]; //각 클러스터 실루엣 계수 총 합의 제곱
        clusterSizes[cluster]++;  //클러스터 내 데이터 개수
    }

    // 전체 실루엣 계수 합계 및 평균 계산
    double totalSilhouetteSum = 0.0;
    for (int c = 0; c < k; c++) {
        if (clusterSizes[c] > 0) {
            double clusterMean = clusterSilhouetteSum[c] / clusterSizes[c]; //각 클러스터 실루엣 계수 평균 저장
            double clusterVariance = (clusterSilhouetteSquaredSum[c] / clusterSizes[c]) - (clusterMean * clusterMean); //각 클러스터 내 데이터의 실루엣 게수 분산
            double clusterStdDev = sqrt(clusterVariance); //각 클러스터 내 데이터의 실루엣 계수 표준 편차
            totalSilhouetteSum += clusterSilhouetteSum[c];

            printf("Cluster %d: Mean Silhouette = %.4f, StdDev = %.4f\n", c, clusterMean, clusterStdDev);
        }
    }

    double totalMeanSilhouette = totalSilhouetteSum / n;
    printf("Overall Mean Silhouette = %.4f\n", totalMeanSilhouette);

    free(clusterSilhouetteSum);
    free(clusterSilhouetteSquaredSum);
    free(clusterSizes);
}
