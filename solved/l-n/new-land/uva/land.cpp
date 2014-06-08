#include <cstdio>
#include <cstring>


#define MAXN 2000


typedef unsigned int u32;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};

typedef int AreaT;
AreaT areas[MAXN];
int stk[MAXN], stk_top;
AreaT histo_area(AreaT *h, int n)
{
	stk_top = 0;
	for (int i = 0; i < n; ++i) {
		while (stk_top > 0 && h[ stk[stk_top-1] ] >= h[i]) --stk_top;
		int bound = stk_top > 0 ? stk[stk_top - 1] : -1;
		areas[i] = i - bound;
		stk[stk_top++] = i;
	}

	stk_top = 0;
	for (int i = n-1; i >= 0; --i) {
		while (stk_top > 0 && h[ stk[stk_top-1] ] >= h[i]) --stk_top;
		int bound = stk_top > 0 ? stk[stk_top - 1] : n;
		areas[i] += bound - i - 1;
		stk[stk_top++] = i;
	}

	AreaT ans = 0;
	for (int i = 0; i < n; ++i)
		if (h[i] > 0 && areas[i]*h[i] > ans) ans = areas[i]*h[i];
	return ans;
}


int m, n;

char row[MAXN];
int hist[MAXN];
int max_area;


void process_row()
{
	for (int i = 0; i < n; ++i)
		if (row[i] == '0') ++hist[i];
		else hist[i] = 0;

	int curr = histo_area(hist, n);
	if (curr > max_area) max_area = curr;
}

void init()
{
	memset(hist, 0, n * sizeof(int));
	max_area = 0;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		m = rr.next_u32();
		n = rr.next_u32();

		init();

		while (m--) {
			int k = rr.next_u32();
			int c = rr.next_u32();

			char x = c == 0 ? '0' : '1';
			int j = 0;
			while (k--) {
				int p = rr.next_u32();
				while (p--) row[j++] = x;
				x = x == '0' ? '1' : '0';
			}
			process_row();
		}

		printf("Case %d: %d\n", ++ncase, max_area);
	}

	return 0;
}
