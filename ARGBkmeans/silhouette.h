#pragma once
#ifndef SILHOUETTE_H
#define SILHOUETTE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include "euclidean.h"

double* silhouetteCoefficient(double** data, int* labels, double** centers, int n, int k, int dim);
void evaluateSilhouette(double* silhouetteScores, int* labels, int n, int k);

#endif