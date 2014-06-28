/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem J: RhyHan and the King - Hard
 *
 * Keywords:
 *   - binary indexed tree
 */

#include <cstdio>
#include <cstring>


#define MAXN 100000

#define GetLSB(x) ((x) & -(x))
#define ClrLSB(x) (x &= ~GetLSB(x))


//
// Binary Indexed Tree
//
const int MAXBIT = MAXN;
typedef int BitT;
struct Bit {
	BitT f[MAXBIT + 1];
	int n;
	void init(int N) { n=N; memset(f, 0, sizeof(BitT) * (n+1)); }
	void add(int i, BitT v) { while (i <= n) { f[i] += v; i += GetLSB(i); } }
	BitT query(int i) { BitT r = 0; for (;i; ClrLSB(i)) r += f[i]; return r; }
	BitT query(int from, int to) { return query(to) - query(from - 1); }
};


int N, M;
Bit tree;


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		tree.init(N);
		for (int i = 1; i <= N; ++i) {
			int x;
			scanf("%d", &x);
			tree.add(i, x);
		}

		printf("Case %d:\n", ++ncase);
		scanf("%d", &M);
		while (M--) {
			int cmd;
			scanf("%d", &cmd);
			if (cmd == 1) {
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%d\n", tree.query(x, y));
			}
			else if (cmd == 2) {
				int x, y, p;
				scanf("%d%d%d", &x, &y, &p);
				tree.add(x, -p);
				tree.add(y, p);
			}
		}
	}

	return 0;
}
