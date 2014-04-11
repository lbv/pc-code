//
// Template for an auxiliary program, useful for geometry problems.
// The purpose is to create a GnuPlot script, to plot the relevant
// geometric figures.
//

#include <cstdio>


char f1[128];
char f2[128];

int main()
{
	FILE *gplot = fopen("graph/plot.gp", "w");
	fprintf(gplot, "set grid xtics ytics\n");
	fprintf(gplot, "set nokey\n");
	fprintf(gplot, "set size square\n");
	fprintf(gplot, "set style line 1 lw 3\n");
	fprintf(gplot, "set style line 2 pt 7 lc rgb \"black\" ps 2\n");
	fprintf(gplot, "set term pngcairo size 400,300 enhanced font 'Verdana,10'\n");

	int T;
	scanf("%d", &T);

	int n, q, x, y;

	// This example creates two data files, one for polygons, one for points
	for (int cas = 1; cas <= T; ++cas) {
		sprintf(f1, "graph/poly%02d.dat", cas);
		sprintf(f2, "graph/q%02d.dat", cas);

		FILE *poly = fopen(f1, "w");
		FILE *quer = fopen(f2, "w");

		scanf("%d", &n);

		int firstx, firsty;
		scanf("%d%d", &firstx, &firsty);
		fprintf(poly, "%d %d\n", firstx, firsty);

		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			fprintf(poly, "%d %d\n", x, y);
		}
		fprintf(poly, "%d %d\n", firstx, firsty);

		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			scanf("%d%d", &x, &y);
			fprintf(quer, "%d %d\n", x, y);
		}

		fclose(poly);
		fclose(quer);

		fprintf(gplot, "set output \"case%02d.png\"\n", cas);
		fprintf(gplot, "plot \"poly%02d.dat\" with lines ls 1,\\\n", cas);
		fprintf(gplot, "\t\"q%02d.dat\" with points ls 2\n", cas);
	}
	fclose(gplot);

	return 0;
}
