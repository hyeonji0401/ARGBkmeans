#include "kmeans.h"

int main() {
    int n = ROWS;     // 데이터 수
    int dim = COLS;   // 데이터 차원
    int k = 3;     // 군집 수

    // 예시 데이터
    double data[ROWS][COLS]; // 정적 배열 선언

    // CSV 파일 읽기
    read_csv(data, "argb.csv");
    

    // 2차원 배열을 동적으로 변환
    double** dataptr = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        dataptr[i] = (double*)malloc(dim * sizeof(double));
        for (int j = 0; j < dim; j++) {
            dataptr[i][j] = data[i][j];
        }
    }


    // kmeans 실행
    kmeans(dataptr, n, dim, k);

    // 메모리 해제
    for (int i = 0; i < n; i++) {
        free(dataptr[i]);
    }
    free(dataptr);

    return 0;
}
