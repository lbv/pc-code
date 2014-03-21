#include <cstdio>
#include <limits>
#include <map>
#include <vector>
using namespace std;

#define Max(t) (numeric_limits<t>::max())

typedef unsigned long long u64;

typedef pair<u64, u64> UU;
typedef map<u64, int>  UIM;
typedef map<u64, UU>   UUUM;

typedef vector<u64> UV;

u64 n;

UIM  counts;
UUUM pairs;

void prepare()
{
    UV efib;
    efib.push_back(0);
    efib.push_back(1);
    efib.push_back(1);

    int n = 3;

    while (true) {
        if (efib[n - 3] > Max(u64) - efib[n - 2])
            break;

        efib.push_back(efib[n - 3] + efib[n - 2]);
        ++n;
    }

    int q = efib.size();

    UV uniq;
    u64 prev = 0;
    for (int i = 0; i < q; ++i) {
        if (efib[i] == prev) continue;
        uniq.push_back(efib[i]);
        prev = efib[i];
    }

    q = uniq.size();

    for (int i = 0; i < q; ++i)
        for (int j = i; j < q; ++j) {
            if (uniq[i] > Max(u64) - uniq[j]) continue;

            u64 s = uniq[i] + uniq[j];
            ++counts[s];
            if (counts[s] == 1)
                pairs[s] = UU(uniq[i], uniq[j]);
        }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%llu", &n);

        printf("Case %d: ", ++ncase);

        if (counts[n] > 0)
            printf("%d %llu %llu\n", counts[n], pairs[n].first, pairs[n].second);
        else
            puts("Invalid Number");
    }

    return 0;
}
