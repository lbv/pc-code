#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

struct Data {
    int v;  // value
    int n;  // occurrences
    int p;  // original position of data, to break ties
    Data(int V, int N, int P) : v(V), n(N), p(P) {}
    bool operator<(const Data &x) const {
        if (v != x.v) return v < x.v;
        if (n != x.n) return n < x.n;
        return p < x.p;
    }
};

typedef vector<Data> DV;
typedef DV::iterator DVi;

int select_kth(DVi lo, DVi hi, int k)
{
    if (hi == lo + 1) return lo->v;
    swap(*(lo + (rand() % (hi - lo))), *(hi - 1));
    Data piv = *(hi - 1);
    DVi x = lo;
    int lt = 0;
    for (DVi i = lo, I = hi - 1; i != I; ++i)
        if (*i < piv) { swap(*i, *x); lt += x->n, ++x; }
    swap(*x, *(hi - 1));
    if (k < lt) return select_kth(lo, x, k);
    if (k >= lt + x->n) return select_kth(x + 1, hi, k - lt - x->n);
    return x->v;
}

int q;

int main()
{
    srand(1000003);
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%*d%*d%d", &q);

        DV xs;
        DV ys;

        int n = 0;  // total amount of people

        while (q--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            xs.push_back(Data(u, w, q));
            ys.push_back(Data(v, w, q));
            n += w;
        }

        int k = n / 2;

        printf("Case %d: %d %d\n", ++ncase,
               select_kth(xs.begin(), xs.end(), k),
               select_kth(ys.begin(), ys.end(), k));
    }

    return 0;
}
