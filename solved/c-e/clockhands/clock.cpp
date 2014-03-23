#include <algorithm>
#include <cstdio>
using namespace std;

int H, M;
double a, b;  // angles for the two hands

int main()
{
    while (true) {
        scanf("%d:%d", &H, &M);
        if (H == 0 && M == 0) break;

        a = H*30 + 1.0*M/2.0;
        b = M*6;

        double x = a - b;
        double y = b - a;
        if (x < 0) x += 360;
        if (y < 0) y += 360;

        printf("%.3lf\n", min(x, y));
    }

    return 0;
}
