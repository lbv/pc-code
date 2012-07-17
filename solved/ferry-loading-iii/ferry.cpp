#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;


#define INF   10010

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


struct Node {
    int c;  // car serial
    int a;  // arrival time
    Node(int C, int A) : c(C), a(A) {}
    bool operator<(const Node &x) const {
        if (c != x.c) return c < x.c;
        return a < x.a;
    }
};
typedef queue<Node>  NQ;
typedef vector<Node> NV;

int n, t, m;

int a;  // arrive time
char side[8];

NQ q[2];  // the queues from both sides -- left: 0, right: 1


int main()
{
    int c;
    scanf("%d", &c);

    bool first = true;
    while (c--) {
        scanf("%d%d%d", &n, &t, &m);

        for (int i = 0; i < m; ++i) {
            scanf("%d%s", &a, side);
            if (side[0] == 'l')
                q[0].push(Node(i, a));
            else
                q[1].push(Node(i, a));
        }

        if (first) first = false;
        else putchar('\n');

        int T = 0;   // current time
        int s = 0;   // side of the river where the ferry is
        NQ  f;       // ferry

        NV arrivals;

        while (! q[0].empty() || ! q[1].empty()) {
            int next = INF;
            if (! q[0].empty())
                next = q[0].front().a;
            if (! q[1].empty())
                next = min(next, q[1].front().a);

            if (next > T) T = next;    // the ferry waits ..

            int onboard = 0;
            while (onboard < n && ! q[s].empty() && q[s].front().a <= T) {
                f.push(q[s].front());
                q[s].pop();
                ++onboard;
            }
            s = (s + 1) % 2;
            T += t;
            while (! f.empty()) {
                arrivals.push_back(Node(f.front().c, T));
                f.pop();
            }
        }

        sort(arrivals.begin(), arrivals.end());
        cFor (NV, n, arrivals)
            printf("%d\n", n->a);
    }

    return 0;
}
