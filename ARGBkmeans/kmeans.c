#include"kmeans.h"

// K-means 클러스터링
void kmeans(double** data, int n, int dim, int k) {
    double** centers = (double**)malloc(k * sizeof(double*));
    for (int i = 0; i < k; i++) {
        centers[i] = (double*)malloc(dim * sizeof(double));
    }

    int* labels = (int*)malloc(n * sizeof(int));

    //0~1사이로 정규화
    normalize(data, n, dim);

    // 초기 중심점 설정
    findFirstCenter(data, centers, n, dim, k);

    // 반복 수행
    int iter = 0;
    int centerChanged;
    do {
        // 이전 중심점을 저장
        double** oldCenters = (double**)malloc(k * sizeof(double*));
        for (int i = 0; i < k; i++) {
            oldCenters[i] = (double*)malloc(dim * sizeof(double));
            for (int j = 0; j < dim; j++) {
                oldCenters[i][j] = centers[i][j];
            }
        }

        // 데이터 클러스터 배정
        assignCluster(data, centers, labels, n, dim, k);

        // 새로운 중심점 찾기
        findNewCenter(data, centers, labels, n, dim, k);

        // 중심점이 바뀌었는지 확인
        centerChanged = isCenterChanged(oldCenters, centers, dim, k);

        // 메모리 해제
        for (int i = 0; i < k; i++) {
            free(oldCenters[i]);
        }
        free(oldCenters);

        iter++;
    } while (centerChanged && iter < MAX_ITER);

    // 실루엣 계수 계산
    double* silhouetteScores = silhouetteCoefficient(data, labels, centers, n, k, dim);

    // 최종 중심점 출력
    printf("최종 중심점:\n");
    for (int i = 0; i < k; i++) {
        printf("Cluster %d Center: ", i);
        for (int j = 0; j < dim; j++) {
            printf("%lf ", centers[i][j]);
        }
        printf("\n");
    }

    // 각 중심점에 할당된 데이터 출력
    //printf("\n각 중심점에 할당된 데이터:\n");
    //printClusterData(data, labels, n, dim, k, silhouetteScores);

    // 각 클러스터의 평균 실루엣 계수와 편차 계산
    evaluateSilhouette(silhouetteScores, labels, n, k);

    printf("반복 횟수: %d", iter);

    // 메모리 해제
    free(silhouetteScores);

    // 메모리 해제
    for (int i = 0; i < k; i++) {
        free(centers[i]);
    }
    free(centers);
    free(labels);
}