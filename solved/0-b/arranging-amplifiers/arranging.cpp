#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100000

#define Clr(m) memset(m, 0, sizeof(m))


typedef unsigned int u32;

struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};


int N, n;
int as[MAXN];
int cnt[4];  // count of the first 3 positive integers


void print(int x)
{
	if (N++ > 0) putchar(' ');
	printf("%d", x);
}

bool cmp(int a, int b) { return a > b; }
void solve()
{
	N = 0;

	for (int i = 0; i < cnt[1]; ++i) print(1);
	sort(as, as + n, cmp);
	for (int i = 0; i < n; ++i) print(as[i]);

	if (cnt[2] > 0 && n == 0 && cnt[3] == 1) {
		print(2);
		--cnt[2];
	}
	for (int i = 0; i < cnt[3]; ++i) print(3);
	for (int i = 0; i < cnt[2]; ++i) print(2);

	putchar('\n');
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	while (T--) {
		N = rr.next_u32();
		n = 0;

		Clr(cnt);
		while (N--) {
			int x = rr.next_u32();

			if (1 <= x && x <= 3) ++cnt[x];
			else as[n++] = x;
		}

		solve();
	}

	return 0;
}
