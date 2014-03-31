#include <cstdio>


#define MAXRECT 10


struct Rect {
	double x1, y1, x2, y2;

	Rect() {}
	Rect(double X1, double Y1, double X2, double Y2):
		x1(X1), y1(Y1), x2(X2), y2(Y2) {}

	bool contains(double x, double y) const {
		return x1 < x && x < x2 && y2 < y && y < y1;
	}
};


Rect rs[MAXRECT];
int nrect;


void read_rectangles()
{
	char c;
	nrect = 0;

	while (true) {
		scanf(" %c", &c);
		if (c == '*') return;

		double x1, y1, x2, y2;
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);

		rs[nrect++] = Rect(x1, y1, x2, y2);
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
		for (int i = 0; i < nrect; ++i)
			if (rs[i].contains(x, y)) {
				printf("Point %d is contained in figure %d\n", npoint, i + 1);
				++cnt;
			}

		if (cnt == 0)
			printf("Point %d is not contained in any figure\n", npoint);
	}
}

int main()
{
	read_rectangles();
	read_points();

	return 0;
}
