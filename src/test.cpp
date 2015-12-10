#include <cstdio>
int main(){
    double x[10] = {3,8,4,10,9,2,1,5,6,7};
    double res[10];
    bestbeforemaxdd(x, 10, 5, 1, res);
    for (int i=0; i<10; i++){
        printf("%d,%lf,%lf\n", i, x[i], res[i]);
    }
}
