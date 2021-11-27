#include <stdio.h>
#include <stdlib.h> // rand() 함수 포함 라이브러리

void ten_to_two(unsigned);
int main(void)
{
    int k = 3, j = 4;
    printf("%d\n", 10 << k);
    ten_to_two(-1<<k);
    ten_to_two(~(-1<<k)<<j);

    int x = 1;
    int y = rand();

    printf("%d\n", ((x+y)<<5) + x - y == 31*y + 33*x); 
    return 0;

}
void ten_to_two(unsigned n) {
    unsigned a = 0x8000; // 1000 0000 0000 0000(2)
    for (int i = 0; i < 16; i++) {
        if ((a & n) == a)
            printf("1");
        else
            printf("0");
        a >>= 1;
    }
    printf("\n");
}