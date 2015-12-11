#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <R.h>
#include <Rdefines.h>


#include "maxdd.h"

void bestbeforemaxdd(double *x, int *r, double *threshold, int *dir, int *results){
    best_before_maxdd(x, r[0], threshold[0], dir[0] > 0 ? 1 : -1, results);
}
