#include"kmeans.h"

// K-means 클러스터링
void kmeans(double** data, int n, int dim, int k) {
    double** centers = (double**)malloc(k * sizeof(double*));
    for (int i = 0; i < k; i++) {
        centers[i] = (double*)malloc(dim * sizeof(double));
    }

    int* labels = (int*)malloc(n * sizeof(int));

    auto normalizeStart = std::chrono::high_resolution_clock::now();
    //0~1사이로 정규화
    normalize(data, n, dim);
    auto normalizeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> normalizeElapsed = normalizeEnd - normalizeStart;

   
    auto firstCenterStart = std::chrono::high_resolution_clock::now();
    // 초기 중심점 설정
    findFirstCenter(data, centers, n, dim, k);
    auto firstCenterEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> firstCenterElapsed = firstCenterEnd - firstCenterStart;
   

    std::chrono::duration<double, std::milli> assignElapsed(0);
    std::chrono::duration<double, std::milli> newCenterElapsed(0);

    auto clusterStart = std::chrono::high_resolution_clock::now();
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

        auto assignStart = std::chrono::high_resolution_clock::now();
        // 데이터 클러스터 배정
        assignCluster(data, centers, labels, n, dim, k);
        auto assignEnd = std::chrono::high_resolution_clock::now();
        assignElapsed += assignEnd - assignStart;

        auto newCenterStart = std::chrono::high_resolution_clock::now();
        // 새로운 중심점 찾기
        findNewCenter(data, centers, labels, n, dim, k);
        auto newCenterEnd = std::chrono::high_resolution_clock::now();
        newCenterElapsed += newCenterEnd - newCenterStart;

        // 중심점이 바뀌었는지 확인
        centerChanged = isCenterChanged(oldCenters, centers, dim, k);

        // 메모리 해제
        for (int i = 0; i < k; i++) {
            free(oldCenters[i]);
        }
        free(oldCenters);

        iter++;
    } while (centerChanged && iter < MAX_ITER);
    auto clusterEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> clusterElapsed = clusterEnd - clusterStart;
   
    std::cout << "정규화 시간: " << normalizeElapsed.count() << " ms" << std::endl;
    std::cout << "kmeans++ 시간: " << firstCenterElapsed.count() << " ms" << std::endl;
    std::cout << "할당 전체 시간: " << assignElapsed.count() << " ms" << std::endl;
    std::cout << "할당 평균 시간: " << assignElapsed.count()/(double)iter << " ms" << std::endl;
    std::cout << "중심점 갱신 전체 시간: " << newCenterElapsed.count() << " ms" << std::endl;
    std::cout << "중심점 갱신 평균 시간: " << newCenterElapsed.count()/(double)iter << " ms" << std::endl;
    std::cout << "전체 kmeans 시간: " << clusterElapsed.count() << " ms" << std::endl;



    // 실루엣 계수 계산
    //double* silhouetteScores = silhouetteCoefficient(data, labels, centers, n, k, dim);

    //// 최종 중심점 출력
    //printf("최종 중심점:\n");
    //for (int i = 0; i < k; i++) {
    //    printf("Cluster %d Center: ", i);
    //    for (int j = 0; j < dim; j++) {
    //        printf("%lf ", centers[i][j]);
    //    }
    //    printf("\n");
    //}

    // 각 중심점에 할당된 데이터 출력
    //printf("\n각 중심점에 할당된 데이터:\n");
    //printClusterData(data, labels, n, dim, k, silhouetteScores);

    //// 각 클러스터의 평균 실루엣 계수와 편차 계산
    //evaluateSilhouette(silhouetteScores, labels, n, k);

    //printf("반복 횟수: %d", iter);

    //// 메모리 해제
    //free(silhouetteScores);

    // 메모리 해제
    for (int i = 0; i < k; i++) {
        free(centers[i]);
    }
    free(centers);
    free(labels);
}