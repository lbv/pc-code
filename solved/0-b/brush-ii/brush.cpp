#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 50000


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};


int N, w;
int ys[MAXN];


int solve()
{
	sort(ys, ys + N);

    // current y position of the top of the brush
    int y = ys[0] - 1;
    int moves = 0;

    for (int i = 0; i < N; ++i)
        if (ys[i] > y) {
            ++moves;
            y = ys[i] + w;
        }

	return moves;
}

int main()
{
	Reader rr;

	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		w = rr.next_u32();

		for (int i = 0; i < N; ++i) {
			rr.next_u32();
			ys[i] = rr.next_int();
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}
