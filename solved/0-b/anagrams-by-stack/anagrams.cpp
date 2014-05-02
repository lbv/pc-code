#include <cstdio>
#include <cstring>


#define MAXLEN 1024


char S[MAXLEN];
char T[MAXLEN];
int s, t;

char stk[MAXLEN];

int stk_top;  // top of stack
int sp, tp;   // pointers in S, T

char seq[MAXLEN];  // sequence of operations
int n;             // number of operations


void dfs()
{
	if (tp == t) {
		if (n > 0) printf("%c", seq[0]);
		for (int i = 1; i < n; ++i)
			printf(" %c", seq[i]);
		putchar('\n');
		return;
	}

	if (sp < s) {
		stk[stk_top++] = S[sp++];
		seq[n++] = 'i';

		dfs();

		--stk_top, --sp, --n;
	}

	if (stk_top > 0 && tp < t && stk[stk_top - 1] == T[tp]) {
		char c = stk[--stk_top];
		++tp;
		seq[n++] = 'o';

		dfs();

		stk[stk_top++] = c;
		--tp, --n;
	}
}

void solve()
{
	stk_top = sp = tp = n = 0;
	s = strlen(S);
	t = strlen(T);

	if (s != t) return;

	dfs();
}

int main()
{
	while (gets(S) && gets(T)) {
		puts("[");
		solve();
		puts("]");
	}

	return 0;
}
