#pragma once
#pragma once
#ifndef INOUTPUTCLUSTER_H
#define INOUTPUTCLUSTER_H

#include <stdio.h>
#include <stdlib.h>

#define ROWS 12500
#define COLS 4

void read_csv(double data[ROWS][COLS], const char* filename);
void printClusterData(double** data, int* labels, int n, int dim, int k, double* silhouette);

#endif