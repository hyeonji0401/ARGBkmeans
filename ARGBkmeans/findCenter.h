#pragma once
#ifndef FINDCENTER_H
#define FINDCENTER_H

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include "euclidean.h"

void findFirstCenter(double** data, double** centers, int n, int dim, int k);
void findNewCenter(double** data, double** centers, int* labels, int n, int dim, int k);
int isCenterChanged(double** oldCenters, double** newCenters, int dim, int k);

#endif