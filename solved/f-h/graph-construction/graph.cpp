#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 10000


typedef long long i64;


struct Node {
    int n;  // sequence number
    i64 p;  // prefix sum
    Node(int N, i64 P) : n(N), p(P) {}
    bool operator<(const Node &x) const { return n > x.n; }
};
typedef vector<Node> NV;
typedef NV::iterator NVi;


int n;
int ns[MAXN];
bool neg;
i64 tot;


bool solve()
{
    if (neg || tot % 2 != 0) return false;
    sort(ns, ns + n);

    NV seq;
    seq.push_back(Node(0, 0));  // dummy value to shift array indices

    i64 p = 0;

    for (int i = n - 1; i >= 0; --i) {
        p += ns[i];
        seq.push_back(Node(ns[i], p));
    }

    NVi lst = seq.end(); --lst;
    NVi it = seq.begin(); ++it;
    for (int k = 1; k <= n; ++k, ++it) {
        i64 sum_left = seq[k].p;

        i64 kk = k;
        i64 t1 = kk * (kk - 1);

        i64 t2 = 0;

        if (k < n) {
            NVi nxt = it + 1;
            NVi j = upper_bound(nxt, seq.end(), Node(k, 0));

            t2 += kk * (j - nxt);
            if (j < seq.end()) {
                --j;
                t2 += lst->p - j->p;
            }
        }

        if (sum_left > t1 + t2) return false;
    }
    return true;
}

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        neg = false;
        tot = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &ns[i]);
            if (ns[i] < 0) neg = true;
            tot += ns[i];
        }

        if (solve())
            puts("Possible");
        else
            puts("Not possible");
    }

    return 0;
}
