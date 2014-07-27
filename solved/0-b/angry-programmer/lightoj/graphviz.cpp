#include <cstdio>


void handle(int kase)
{
	char fname[64];
	sprintf(fname, "case%02d.dot", kase);
	FILE *out = fopen(fname, "w");

	int M, W;
	scanf("%d%d", &M, &W);

	fprintf(out, "graph G {\n");

	fprintf(out, "\t%d [shape=\"doublecircle\"]\n", 1);
	fprintf(out, "\t%d [shape=\"doublecircle\"]\n", M);

	for (int i = 2; i < M; ++i) {
		int cap;
		scanf("%d", &cap);
		fprintf(out, "\t%d [label=<%d<BR/><FONT COLOR=\"blue\">%d</FONT>>]\n",
			i, i, cap);
	}

	while (W--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		fprintf(out, "\t%2d -- %2d [label=<<FONT COLOR=\"blue\">%d</FONT>>]\n",
			u, v, w);
	}

	fprintf(out, "}\n");
	fclose(out);
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int i = 1; i <= T; ++i)
		handle(i);

	return 0;
}
