#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000


struct Job {
    int t, s, i;

    bool operator<(const Job &x) const {
        int p = t * x.s, q = x.t * s;
        if (p != q) return p < q;
        return i < x.i;
    }
};


int N;
Job jobs[MAXN];


int main()
{
    int T;
    scanf("%d", &T);

    for (int cas = 0; cas < T; ++cas) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &jobs[i].t, &jobs[i].s);
            jobs[i].i = i + 1;
        }

        sort(jobs, jobs + N);

        if (cas > 0) putchar('\n');
        for (int i = 0; i < N; ++i) {
            if (i > 0) putchar(' ');
            printf("%d", jobs[i].i);
        }
        putchar('\n');
    }

    return 0;
}
