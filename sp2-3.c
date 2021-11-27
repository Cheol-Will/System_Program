#include <stdio.h>
#include <limits.h>
int main(void)
{
    int x;
    float y;
    printf("%d\n", y == (float) y);
    printf("%d\n", x == (int)(float) x);

    return 0;
}