#include <cstdio>
#include <vector>
using namespace std;


#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef vector<int> IV;


int d;
IV ns[9];
const char fmts[4][8] = {
    "%02d\n",
    "%04d\n",
    "%06d\n",
    "%08d\n"
};


int ipow(int b, int e)
{
    int res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}

void prepare()
{
    for (int i = 2; i <= 8; i += 2) {
        int top = ipow(10, i);
        int half = ipow(10, i/2);

        for (int a = 0; a < half; ++a) {
            int a2 = a*a;
            if (a2 > top) break;

            int a_shifted = a * half;

            for (int b = 0; b < half; ++b) {
                int sum = (a + b) * (a + b);
                if (sum > top) break;

                if (sum == a_shifted + b)
                    ns[i].push_back(sum);
            }
        }
    }
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &d) != 1) break;

        cFor (IV, n, ns[d])
            printf(fmts[d/2 - 1], *n);
    }

    return 0;
}
