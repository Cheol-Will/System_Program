#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.141592
double normal(float stddev, float mean);

int main(void)
{   
    double a[10];
    for(int i = 0; i<10; i++)
        a[i] = normal(1, 0);
    for(int i = 0; i<10; i++)
        printf("%lf ", a[i]);
}
// 정규분포 확률변수 발생 Routine

double normal(float stddev, float mean)
{
    double r1, r2, z1, z2, result, dt, num;
    int i;

    result = 0.0;
    dt = 1.0/100.0;

    for (i = 0; i < 100; i++)
    {
        r1 = (float)rand() / (float)RAND_MAX;
        r2 = (float)rand() / (float)RAND_MAX;

        z1 = sqrt(-2 * log(r1)) * cos(2 * PI * r2);
        z2 = sqrt(-2 * log(r1)) * sin(2 * PI * r2);

        num = (mean * dt) + (stddev *z1 * sqrt(dt));
        result += num;
    }
    return result;
}