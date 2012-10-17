#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
using namespace std;


typedef unsigned int u32;

typedef stack<int> IS;
typedef queue<int> IQ;
typedef vector<IQ> IQV;


int N;
u32 S, Q;
IQV qs;
IS st;
int np;  // number of packages to deliver


int solve()
{
    int t = 0;

    int station = 1;
    while (np > 0) {
        while (! st.empty()) {
            if (st.top() == station) {
                st.pop();
                ++t;
                --np;
                continue;
            }
            if (qs[station].size() >= Q) break;
            int p = st.top();
            st.pop();
            ++t;
            qs[station].push(p);
        }
        while (qs[station].size() > 0 && st.size() < S) {
            int p = qs[station].front();
            qs[station].pop();
            st.push(p);
            ++t;
        }
        if (np == 0) break;

        station = station == N ? 1 : station + 1;
        t += 2;
    }

    return t;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%u%u", &N, &S, &Q);

        qs = IQV(N + 1);
        st = IS();
        np = 0;

        for (int i = 1; i <= N; ++i) {
            int q;
            scanf("%d", &q);

            while (q--) {
                int p;
                scanf("%d", &p);
                qs[i].push(p);
                ++np;
            }
        }

        printf("%d\n", solve());
    }

    return 0;
}
