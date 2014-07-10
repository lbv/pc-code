#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 2000

#define ClrN(m,n,t) memset(m, 0, sizeof(t)*(n))


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
	AreaT ans = 0;
	for (int i = n-1; i >= 0; --i) {
		while (stk_top > 0 && h[ stk[stk_top-1] ] >= h[i]) --stk_top;
		int bound = stk_top > 0 ? stk[stk_top - 1] : n;
		areas[i] += bound - i - 1;
		stk[stk_top++] = i;

		AreaT sz = min(areas[i], h[i]);
		if (sz > ans) ans = sz;
	}

	return ans;
}


int N;

char row[MAXN+1];
int hist[MAXN];
int max_size;


void process_row()
{
	for (int i = 0; i < N; ++i)
		if (row[i] == '.') ++hist[i];
		else hist[i] = 0;

	int curr = histo_area(hist, N);
	if (curr > max_size) max_size = curr;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);

		max_size = 0;
		ClrN(hist, N, int);

		for (int i = 0; i < N; ++i) {
			scanf("%s", row);
			process_row();
		}

		printf("%d\n", max_size);
	}

	return 0;
}
