#include"inoutputCluster.h"

void read_csv(double data[ROWS][COLS], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    int row = 0;

    // 첫 번째 줄은 헤더이므로 무시
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf_s(line, "%lf,%lf,%lf,%lf", &data[row][0], &data[row][1], &data[row][2], &data[row][3]);
        row++;
    }

    fclose(file);
}