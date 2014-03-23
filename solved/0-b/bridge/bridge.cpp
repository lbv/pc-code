#include <algorithm>
#include <cstdio>
#include <list>
#include <vector>
using namespace std;


#define INF 110

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef pair<int, int> II;
typedef vector<II>     IIV;
typedef list<int>      IL;
typedef IL::iterator   ILi;


struct Move {
    ILi a, b;
    int f, cost, time;
    IL r;
    Move(ILi A, ILi B) : a(A), b(B) {}
};

IL people;
IIV moves;
int mintime, fast;
int n;


Move analyze(ILi a, ILi b)
{
    Move m(a, b);
    int t1, t2;

    t1 = *b;
    if (fast < *a)
        t2 = fast, m.f = *a;
    else
        t2 = *a, m.f = min(fast, *b);

    m.time = t1 + t2;
    m.r.push_back(t2);

    m.cost = m.time - (*a + *b - t2);
    return m;
}

void solve()
{
    people.sort();
    mintime = 0;
    fast = INF;
    moves = IIV();

    while (people.size() > 0) {
        if (people.size() <= 2) {
            int a = people.front(); people.pop_front();
            int b = people.size() > 0 ? people.front() : -1;

            mintime += max(a, b);
            moves.push_back(II(a, b));
            break;
        }

        ILi a = people.begin();
        ILi b = people.begin(); ++b;
        Move m = analyze(a, b);
        Move best = m;

        b = people.end(); --b;
        m = analyze(a, b);
        if (m.cost < best.cost) best = m;

        a = b;
        --a;
        m = analyze(a, b);
        if (m.cost < best.cost) best = m;

        moves.push_back(II(*(best.a), *(best.b)));
        moves.push_back(II(best.r.front(), -1));
        mintime += best.time;

        people.erase(best.a);
        people.erase(best.b);
        people.merge(best.r);
        fast = best.f;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;

    while (T--) {
        scanf("%d", &n);

        people = IL();

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            people.push_back(x);
        }

        solve();

        if (first) first = false;
        else putchar('\n');

        printf("%d\n", mintime);
        cFor (IIV, m, moves) {
            printf("%d", m->first);
            if (m->second >= 0)
                printf(" %d", m->second);
            putchar('\n');
        }
    }

    return 0;
}
