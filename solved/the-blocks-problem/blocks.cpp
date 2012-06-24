#include <cstdio>
#include <deque>
#include <stack>
using namespace std;

#define MAXN 25
#define MOVE 1
#define PILE 2
#define ONTO 1
#define OVER 2

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

typedef deque<int> ID;
typedef stack<int> IK;

ID piles[MAXN];

// loc[i] will have the number of the pile where block i is found
int loc[MAXN];

char com[8];
int n;
int com1, com2;
int a, b;
IK aux;

void apply_command()
{
    if (a == b || loc[a] == loc[b]) return;

    int p = loc[a];
    int q = loc[b];
    int x;  // block

    if (com1 == MOVE) {
        while (piles[p].back() != a) {
            x = piles[p].back();
            piles[p].pop_back();
            loc[x] = x;
            piles[x].push_back(x);
        }
    }

    if (com2 == ONTO) {
        while (piles[q].back() != b) {
            x = piles[q].back();
            piles[q].pop_back();
            loc[x] = x;
            piles[x].push_back(x);
        }
    }

    while (true) {
        x = piles[p].back();
        piles[p].pop_back();
        aux.push(x);

        if (x == a) break;
    }

    while (! aux.empty()) {
        x = aux.top(); aux.pop();
        loc[x] = q;
        piles[q].push_back(x);
    }
}

int main()
{
    while (true) {
        if (scanf("%d", &n) != 1) break;

        for (int i = 0; i < n; ++i) {
            piles[i].clear();
            piles[i].push_back(i);
            loc[i] = i;
        }

        while (true) {
            scanf("%s", com);
            if (com[0] == 'q') break;

            com1 = com[0] == 'm' ? MOVE : PILE;
            scanf("%d%s%d", &a, com, &b);
            com2 = com[1] == 'v' ? OVER : ONTO;

            apply_command();
        }

        for (int i = 0; i < n; ++i) {
            printf("%d:", i);

            cFor (ID, x, piles[i])
                printf(" %d", *x);
            putchar('\n');
        }
    }

    return 0;
}
