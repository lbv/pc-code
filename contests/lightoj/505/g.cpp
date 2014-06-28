/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem G: Lets Make Google
 *
 * Keywords:
 *   - strings
 *   - binary search
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 1000
#define MAXLEN 1000


struct Word {
	char w[MAXLEN + 1];

	void read() { scanf("%s", w); }
	bool operator<(const Word &x) const { return strcmp(w, x.w) < 0; }
	bool operator==(const Word &x) const { return strcmp(w, x.w) == 0; }
};

Word dict[MAXN];
char str[MAXLEN + 1];
int N, M;


void process()
{
	int len = strlen(str);

	int lo = 0, hi = N - 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		int c = strncmp(dict[mid].w, str, len);
		if (c >= 0) hi = mid-1;
		else lo = mid+1;
	}

	if (lo >= N || strncmp(dict[lo].w, str, len) != 0) {
		puts("No Match");
		return;
	}

	for (int i = lo; i < N && strncmp(dict[i].w, str, len) == 0; ++i)
		puts(dict[i].w);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
			dict[i].read();

		sort(dict, dict + N);
		N = unique(dict, dict + N) - dict;

		printf("Case %d:\n", ++ncase);
		scanf("%d", &M);
		while (M--) {
			scanf("%s", str);
			process();
		}
	}

	return 0;
}
