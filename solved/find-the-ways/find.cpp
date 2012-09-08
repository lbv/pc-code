#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


typedef vector<double> DV;


// logs[i] will have the value of log10(i!)
DV logs;
int maxlog;

int n, k;


double f(int x)
{
    while (x > maxlog) {
        logs.push_back(logs[maxlog] + log10(maxlog + 1));
        ++maxlog;
    }
    return logs[x];
}

int solve()
{
    int digits = 1;
    digits += floor(f(n) - f(k) - f(n-k));
    return digits;
}

int main()
{
    logs.push_back(0); // dummy value to fill the index 0
    logs.push_back(0);
    maxlog = 1;

    while (true) {
        if (scanf("%d%d", &n, &k) != 2) break;
        printf("%d\n", solve());
    }

    return 0;
}
