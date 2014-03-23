#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;


#define MAXN 100000


typedef long long    i64;
typedef vector<int>  IV;
typedef IV::iterator IVi;


IV perm;
int N;
i64 n_swaps;


void merge(IVi lo, IVi hi, IVi mid)
{
    IV x;
    for (IVi a = lo, b = mid; a < mid || b < hi; ) {
        if (a >= mid) { x.push_back(*b++); continue; }
        if (b >= hi) { x.push_back(*a++); continue; }
        if (*a < *b) { x.push_back(*a++); continue; }
        n_swaps += mid - a;
        x.push_back(*b++);
    }
    for (IVi a = lo, b = x.begin(); a < hi; ++a, ++b)
        *a = *b;
}

void merge_sort(IVi lo, IVi hi)
{
    if (hi <= lo + 1) return;
    IVi mid = lo + ((hi - lo) / 2);
    merge_sort(lo, mid);
    merge_sort(mid, hi);
    merge(lo, hi, mid);
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        perm.clear();
        n_swaps = 0;

        while (N--) {
            int x;
            scanf("%d", &x);
            perm.push_back(x);
        }

        merge_sort(perm.begin(), perm.end());

        if (n_swaps % 2 == 0)
            puts("Carlos");
        else
            puts("Marcelo");
    }

    return 0;
}
