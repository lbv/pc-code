#include <cstdio>


#define MAXN 10


int n, m, x;

int q[MAXN];  // double-ended queue
int qsz;      // number of elements
int lt, rt;

char comm[16];


void command()
{
	scanf("%s", comm);

	// printf("  command(%s) qsz(%d) n(%d)\n", comm, qsz, n);
	if (comm[1] == 'u') {
		scanf("%d", &x);

		if (qsz == n) {
			puts("The queue is full");
			return;
		}

		if (comm[4] == 'L') {
			q[lt--] = x;
			if (lt < 0) lt = MAXN - 1;
			printf("Pushed in left: %d\n", x);
		}
		else {
			q[rt++] = x;
			if (rt >= MAXN) rt = 0;
			printf("Pushed in right: %d\n", x);
		}

		++qsz;
		return;
	}

	if (qsz == 0) {
		puts("The queue is empty");
		return;
	}

	if (comm[3] == 'L') {
		if (++lt >= MAXN) lt = 0;
		x = q[lt];
		printf("Popped from left: %d\n", x);
	}
	else {
		if (--rt < 0) rt = MAXN - 1;
		x = q[rt];
		printf("Popped from right: %d\n", x);
	}
	--qsz;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);
		printf("Case %d:\n", ++ncase);

		lt = 0, rt = 1, qsz = 0;
		while (m--)
			command();
	}

	return 0;
}
