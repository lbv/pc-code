#include <cstdio>
#include <list>
#include <vector>
using namespace std;


#define MAXNZ 1000

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


struct Tuple {
    int p;  // position (column)
    int v;  // value
    Tuple(int P, int V) : p(P), v(V) {}
};
typedef list<Tuple> TL;
typedef vector<TL> TLV;


int m, n;
int row[MAXNZ];


int main()
{
    while (true) {
        if (scanf("%d%d", &m, &n) != 2) break;

        TLV mat(n + 1);
        for (int i = 1; i <= m; ++i) {
            int nr;
            scanf("%d", &nr);

            for (int j = 0; j < nr; ++j)
                scanf("%d", &row[j]);

            int v;
            for (int j = 0; j < nr; ++j) {
                scanf("%d", &v);
                mat[row[j]].push_back(Tuple(i, v));
            }
        }

        printf("%d %d\n", n, m);
        for (int i = 1; i <= n; ++i) {
            printf("%d", mat[i].size());
            For (TL, t, mat[i])
                printf(" %d", t->p);
            putchar('\n');

            int j = 0;
            For (TL, t, mat[i]) {
                if (j++ > 0) putchar(' ');
                printf("%d", t->v);
            }
            putchar('\n');
        }

    }

    return 0;
}
