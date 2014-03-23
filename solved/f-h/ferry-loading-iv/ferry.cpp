#include <cstdio>
#include <queue>
using namespace std;


typedef long long i64;
typedef queue<i64> IQ;


char side[8];
IQ q[2];
i64 l, m;

int solve()
{
    int loc = 0;  // 0: left, 1: right

    int moves = 0;
    while (! q[0].empty() || ! q[1].empty()) {
        int sum = 0;
        while (! q[loc].empty() && q[loc].front() + sum <= l) {
            sum += q[loc].front();
            q[loc].pop();
        }

        loc = (loc + 1) % 2;
        ++moves;
    }

    return moves;
}

int main()
{
    int c;
    scanf("%d", &c);

    while (c--) {
        scanf("%lld%lld", &l, &m);

        l *= 100;
        i64 len;

        while (m--) {
            scanf("%lld%s", &len, side);
            if (side[0] == 'l')
                q[0].push(len);
            else
                q[1].push(len);
        }

        printf("%d\n", solve());
    }

    return 0;
}
