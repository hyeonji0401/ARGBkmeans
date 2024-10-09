#pragma once
#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "findCenter.h"
#include "inoutputCluster.h"
#include "silhouette.h"
#include "euclidean.h"
#include "normalize.h"
#include <windows.h>
#include <string.h>
#include <chrono>
#include <iostream>

#define MAX_ITER 1000

void assignCluster(double** data, double** centers, int* labels, int n, int dim, int k);
void kmeans(double** data, int n, int dim, int k);

#endif