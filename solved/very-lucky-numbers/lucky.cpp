#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef long long i64;

typedef vector<i64>  IV;
typedef IV::iterator IVi;


const i64 Max = 1000000000000LL;

i64 A, B;
IV ns;    // very lucky numbers


void uniq(IV &v)
{
    sort(v.begin(), v.end());

    IVi it = unique(v.begin(), v.end());
    v.resize(it - v.begin());
}

void prepare()
{
    IV l1;

    IV x;
    x.push_back(0);
    for (int i = 1; i <= 12; ++i) {
        IV y;

        cFor (IV, n, x) {
            i64 m = *n * 10 + 4;
            l1.push_back(m);
            y.push_back(m);

            m = *n * 10 + 7;
            l1.push_back(m);
            y.push_back(m);
        }
        x = y;
    }

    x = l1;
    uniq(x);
    ns.insert(ns.end(), x.begin(), x.end());

    while (true) {
        IV y;

        cFor (IV, n, l1) {
            i64 q = Max / *n;

            int cnt = 0;
            cFor (IV, m, x) {
                if (*m > q) break;

                i64 p = *n * *m;
                y.push_back(p);
                ++cnt;
            }

            if (cnt == 0) break;
        }

        if (y.size() == 0) break;

        x = y;
        uniq(x);
        ns.insert(ns.end(), x.begin(), x.end());
    }

    uniq(ns);
}

int lucky_count(i64 n)
{
    IVi it = upper_bound(ns.begin(), ns.end(), n);
    return it - ns.begin();
}

int solve()
{
    return lucky_count(B) - lucky_count(A - 1);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%lld%lld", &A, &B);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
