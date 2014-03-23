#include <algorithm>
#include <cstdio>
using namespace std;


int A;

bool angles[181];


void prepare()
{
    int m = 0, h = 0;
    for (int i = 0; i < 720;) {
        int a1 = (m - h) % 360;
        int a2 = (h - m) % 360;
        if (a1 < 0) a1 += 360;
        if (a2 < 0) a2 += 360;
        int a = min(a1, a2);

        angles[a] = true;

        ++i;
        m += 6;
        if (i % 12 == 0) h += 6;
    }
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &A) != 1) break;
        if (angles[A])
            puts("Y");
        else
            puts("N");
    }

    return 0;
}
