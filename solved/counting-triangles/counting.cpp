#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;
typedef vector<int> IV;
typedef IV::iterator IVi;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N, n;
        scanf("%d", &N);

        IV ns;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &n);
            ns.push_back(n);
        }

        sort(ns.begin(), ns.end());

        u64 ans = 0;

        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j) {
                int a = ns[i], b = ns[j];

                IVi lo = ns.begin() + j;
                IVi hi = upper_bound(lo, ns.end(), a+b-1);

                ans += (hi - lo) - 1;
            }

        printf("Case %d: %llu\n", ++ncase, ans);
    }

    return 0;
}
