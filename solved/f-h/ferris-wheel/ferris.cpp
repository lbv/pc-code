#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

typedef list<int> IL;

#define MAXM 20
#define MAXN 20
#define Zero(v) memset(v, 0, sizeof(v))
#define For(t,v,c)   for(t::iterator v=c.begin(); v != c.end(); v++)

int N, M, mintime;

// mask[i] is a bitmask of the seats that person i has tried
int mask[MAXN + 1];

// wheel[i] has the number of the person who is at seat i (or 0 if noone is
// there)
int wheel[MAXM + 1];

#define HasTried(p,s)  (mask[p] & (1 << (s-1)))
#define HasTriedAll(p) (mask[p] == maskall)
#define Tried(p,s)     (mask[p] |= (1 << (s-1)))

void simulation()
{
    Zero(wheel);
    Zero(mask);
    int maskall = (1 << M) - 1;  // mask for all the rides

    IL q;
    for (int i = 1; i <= N; i++) q.push_back(i);
    int people = N;  // people still in the ferris wheel)

    mintime = 5;
    int seat = 1;
    while (true) {
        int p = 0;
        For(IL, i, q)
            if (! HasTried(*i, seat)) {
                p = *i;
                q.erase(i);
                break;
            }

        if (wheel[seat] != 0) {
            if (HasTriedAll(wheel[seat]))
                people--;
            else
                q.push_back(wheel[seat]);
        }
        if (people == 0) break;

        wheel[seat] = p;
        if (p != 0)
            Tried(p, seat);

        mintime += 5;
        seat = seat == M ? 1 : seat+1;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d%d", &N, &M);
        simulation();
        printf("Case %d: %d\n", ncase++, mintime);
    }

    return 0;
}
