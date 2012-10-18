#include <cstdio>
#include <set>
using namespace std;


struct Query {
    int t, p, n;  // time to run, period and number
    Query(int T, int P, int N) : t(T), p(P), n(N) {}
    bool operator<(const Query &x) const {
        if (t != x.t) return t < x.t;
        return n < x.n;
    }
};
typedef set<Query> QS;


QS qs;
char com[16];
int K;


int main()
{
    while (true) {
        scanf("%s", com);
        if (com[0] == '#') break;

        int n, p;
        scanf("%d%d", &n, &p);
        qs.insert(Query(p, p, n));
    }
    scanf("%d", &K);

    while (K--) {
        Query q = *(qs.begin());
        qs.erase(qs.begin());

        printf("%d\n", q.n);

        q.t += q.p;
        qs.insert(q);
    }

    return 0;
}
