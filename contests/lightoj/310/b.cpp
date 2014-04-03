#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;


#define MAXLEN 20


struct Pair {
    int x, i;
    Pair() {}
    Pair(int X, int I) : x(X), i(I) {}
    bool operator<(const Pair &p) const { return x < p.x; }
};


Pair seq[MAXLEN];
int m;


int main()
{
    int n;
    scanf("%d", &n);

    while (n--) {
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int x;
            scanf("%d", &x);
            seq[i] = Pair(x, i);
        }
        sort(seq, seq + m);

        int dist = 0;
        for (int i = 0; i < m; ++i)
            dist += abs(seq[i].i - i);
        printf("%d\n", dist);
    }

    return 0;
}
