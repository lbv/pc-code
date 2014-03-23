#include <cstdio>
#include <vector>
using namespace std;


typedef long long    i64;
typedef vector<i64>  IV;
typedef IV::iterator IVi;


IV seq;
int N;
int n_swaps;


void merge(IVi lo, IVi hi, IVi mid)
{
    IV x;
    for (IVi a = lo, b = mid; a < mid || b < hi; ) {
        if (a >= mid) { x.push_back(*b++); continue; }
        if (b >= hi) { x.push_back(*a++); continue; }
        if (*a <= *b) { x.push_back(*a++); continue; }
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
        if (scanf("%d", &N) != 1) break;

        seq.clear();
        n_swaps = 0;

        while (N--) {
            i64 x;
            scanf("%lld", &x);
            seq.push_back(x);
        }

        merge_sort(seq.begin(), seq.end());

        printf("Minimum exchange operations : %d\n", n_swaps);
    }

    return 0;
}
