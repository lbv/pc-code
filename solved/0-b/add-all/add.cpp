#include <cstdio>
#include <set>
using namespace std;


typedef long long i64;
typedef multiset<i64> IS;


int N;
IS s;


i64 solve()
{
    i64 cost = 0;
    while (true) {
        i64 a = *(s.begin());
        s.erase(s.begin());
        i64 b = *(s.begin());
        s.erase(s.begin());
        cost += a + b;

        if (s.size() == 0) break;
        s.insert(a + b);
    }
    return cost;
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        s = IS();
        while (N--) {
            int n;
            scanf("%d", &n);
            s.insert(n);
        }
        printf("%lld\n", solve());
    }

    return 0;
}
