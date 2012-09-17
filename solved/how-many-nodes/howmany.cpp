#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define MAXNODES (1ULL << 32)


typedef unsigned long long u64;

typedef vector<u64>  UV;
typedef UV::iterator UVi;


u64 n;


UV catalan;
void prepare()
{
    catalan.push_back(1);
    u64 prev = 1;

    for (int i = 1; true; ++i) {
        u64 cat = prev * (4*i - 2) / (i + 1);
        catalan.push_back(cat);
        prev = cat;

        if (cat > MAXNODES) break;
    }
}

int solve()
{
    if (n == 1) return 1;
    UVi it = lower_bound(catalan.begin(), catalan.end(), n);
    return it - catalan.begin();
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%llu", &n) != 1) break;

        printf("%d\n", solve());
    }

    return 0;
}
