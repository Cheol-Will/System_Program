#include <stdio.h>
void twiddle1(long *xp, long *yp);
void twiddle2(long *xp, long *yp);
void swap(long *xp, long *yp);
int main(void)
{   
    long a = 2;
    long b = 2;
    long c = 2;
    // Memory Aliasing
    twiddle1(&a, &a);
    printf("twiddle1: %d\n", a);
    a = 2;
    twiddle2(&a, &a);
    printf("twiddle2: %d\n", a);


    // 그냥 swap
    swap(&a, &b);
    printf("a: %d b: %d\n", a, b);
    return 0;
}   
void twiddle1(long *xp, long *yp){
    *xp += *yp;
    *xp += *yp;
}
void twiddle2(long *xp, long *yp){
    *xp += 2* *yp;
}
void swap(long *xp, long *yp){
    *xp += *yp;
    *yp = *xp - *yp;
    *xp -= *yp;
}