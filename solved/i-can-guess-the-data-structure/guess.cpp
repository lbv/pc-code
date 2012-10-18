#include <cstdio>
#include <queue>
#include <stack>
using namespace std;


typedef priority_queue<int> IP;
typedef queue<int> IQ;
typedef stack<int> IS;


int n, x;
IP p;
IQ q;
IS s;

bool isp, isq, iss;


void check()
{
    int n;

    if (q.size() == 0)
        isq = false;
    else {
        n = q.front();
        q.pop();
        if (n != x) isq = false;
    }

    if (p.size() == 0)
        isp = false;
    else {
        n = p.top();
        p.pop();
        if (n != x) isp = false;
    }

    if (s.size() == 0)
        iss = false;
    else {
        n = s.top();
        s.pop();
        if (n != x) iss = false;
    }
}

int main()
{
    while (true) {
        if (scanf("%d", &n) != 1) break;
        p = IP();
        q = IQ();
        s = IS();
        isp = isq = iss = true;
        while (n--) {
            int op;
            scanf("%d%d", &op, &x);

            if (op == 1) {
                p.push(x);
                q.push(x);
                s.push(x);
            }
            else {
                check();
            }
        }
        if (isp && !isq && !iss)
            puts("priority queue");
        else if (isq && !isp && !iss)
            puts("queue");
        else if (iss && !isp && !isq)
            puts("stack");
        else if (!iss && !isp && !isq)
            puts("impossible");
        else
            puts("not sure");
    }

    return 0;
}
