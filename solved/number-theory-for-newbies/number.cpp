#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
using namespace std;

typedef unsigned long long u64;

#define LEN 12

char hi[LEN], lo[LEN];

int main()
{
    while (true) {
        if (scanf("%s", hi) != 1) break;
        strcpy(lo, hi);

        int len = strlen(hi);

        sort(lo, lo + len);
        sort(hi, hi + len, greater<int>());

        int idx = strspn(lo, "0");
        if (idx < len) swap(lo[0], lo[idx]);

        u64 n1, n2;
        sscanf(hi, "%llu", &n1);
        sscanf(lo, "%llu", &n2);


        u64 diff = n1-n2;

        printf("%llu - %llu = %llu = 9 * %llu\n", n1, n2, diff, diff/9);
    }

    return 0;
}
