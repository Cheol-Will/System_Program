#include <stdio.h>
#include <limits.h>
#include <assert.h>

unsigned f2u(float x) {
  return *(unsigned*)&x;
}

int float_ge(float x, float y) {

    
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;


    return (ux << 1 == 0 && uy << 1 == 0) || /* both zeros */
        (!sx && sy) ||                         /* x > 0, y <= 0 or x >= 0, y < 0 */
        (!sx && !sy && ux >= uy) ||            /* x > 0, y >= 0 or x >= 0, y > 0 */
        (sx && sy && ux <= uy);                /* x < 0, y <= 0 or x <= 0, y < 0 */
}
int main(void)
{
    float x = 3.14, y = 1.59;
    printf("%d\n\n", float_ge(x, y));
    int a = INT_MIN, b = INT_MIN, c = 3;

    double da = (double) a;
    double db = (double) b;
    double dc = (double) c;

    unsigned ua = (unsigned) a;
    unsigned ub = (unsigned) b;


    printf("%lf\n", da + db + dc);
    printf("%lf\n", (double) (a+b+c));


    return 0;
}