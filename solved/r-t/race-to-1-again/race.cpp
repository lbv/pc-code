#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> IV;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

#define MAXN 100000

double E[MAXN + 1];
int N;

void prepare()
{
    IV divs[MAXN + 1];
    for (int i = 2; i <= MAXN; ++i)
        for (int j = i; j <= MAXN; j += i)
            divs[j].push_back(i);

    double sum;
    for (int i = 2; i <= MAXN; ++i) {
        int ndiv = divs[i].size() + 1;  // Adding 1 because 1 is also a divisor

        sum = 1.0;
        cFor (IV, d, divs[i])
            sum += 1.0 + E[i / (*d)];

        E[i] = sum / (ndiv - 1);
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        printf("Case %d: %.8lf\n", ++ncase, E[N]);
    }

    return 0;
}
