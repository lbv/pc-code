#include <cstdio>


#define MAXFIG 10

#define CIRCLE    0
#define RECTANGLE 1


struct Fig {
	int type;
	double x1, y1, x2, y2;

	Fig() {}
	Fig(double x, double y, double r): type(CIRCLE), x1(x), y1(y), x2(r*r) {}

	Fig(double X1, double Y1, double X2, double Y2):
		type(RECTANGLE), x1(X1), y1(Y1), x2(X2), y2(Y2) {}

	bool contains(double x, double y) const {
		if (type == RECTANGLE)
			return x1 < x && x < x2 && y2 < y && y < y1;

		double dx = x - x1, dy = y - y1;
		return dx*dx + dy*dy < x2;
	}
};


Fig figs[MAXFIG];
int nfig;


void read_figures()
{
	char c;
	nfig = 0;

	while (true) {
		scanf(" %c", &c);
		if (c == '*') return;

		else if (c == 'r') {
			double x1, y1, x2, y2;
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);

			figs[nfig++] = Fig(x1, y1, x2, y2);
		}

		else if (c == 'c') {
			double x, y, r;
			scanf("%lf%lf%lf", &x, &y, &r);

			figs[nfig++] = Fig(x, y, r);
		}
	}
}

void read_points()
{
	double x, y;

	int npoint = 1;
	for (;; ++npoint) {
		scanf("%lf%lf", &x, &y);
		if (x == 9999.9 && y == 9999.9) return;

		int cnt = 0;
		for (int i = 0; i < nfig; ++i)
			if (figs[i].contains(x, y)) {
				printf("Point %d is contained in figure %d\n", npoint, i + 1);
				++cnt;
			}

		if (cnt == 0)
			printf("Point %d is not contained in any figure\n", npoint);
	}
}

int main()
{
	read_figures();
	read_points();

	return 0;
}
