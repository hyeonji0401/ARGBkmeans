#include"findCenter.h"

// kmeans++ 방식으로 첫 번째 중심점을 선택하는 함수
void findFirstCenter(double** data, double** centers, int n, int dim, int k) {
    time_t time(time_t * tloc);
    //srand((unsigned)time(NULL));
    int firstCenter = rand() % n;
    for (int i = 0; i < dim; i++) {
        centers[0][i] = data[firstCenter][i];
    }

    for (int c = 1; c < k; c++) {
        double* dist = (double*)malloc(n * sizeof(double));
        double totalDist = 0.0;
        for (int i = 0; i < n; i++) {
            dist[i] = DBL_MAX;
            for (int j = 0; j < c; j++) {
                double d = euclideanDistance(data[i], centers[j], dim);
                if (d < dist[i]) dist[i] = d;
            }

            totalDist += dist[i];
        }
        //여기까지 가장 가까운 중심점까지의 거리 구하는 코드
        double r = ((double)rand() / RAND_MAX) * totalDist;
        double sum = 0.0;
        int nextCenter = -1;
        for (int i = 0; i < n; i++) {
            sum += dist[i];
            if (sum >= r) {
                nextCenter = i;
                break;
            }
        }

        for (int i = 0; i < dim; i++) {
            centers[c][i] = data[nextCenter][i];
        }
        free(dist);
    }
}
