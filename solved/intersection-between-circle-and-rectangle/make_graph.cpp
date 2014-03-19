#include <cstdio>


template <typename T>
struct _Point {
    T x, y;
    _Point(): x(0), y(0) {}
    _Point(T X, T Y) : x(X), y(Y) {}

    T distance(const _Point &p) const {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }

    bool operator<(const _Point &p) const {
        return x < p.x || (x == p.x && y < p.y); }
    bool operator==(const _Point &p) const { return x == p.x && y == p.y; }
    _Point operator-(const _Point &b) const { return _Point(x - b.x, y - b.y); }

    bool collinear(const _Point &b, const _Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
    bool in_box(const _Point &a, const _Point &b) const {
        T lox = min(a.x, b.x), hix = max(a.x, b.x);
        T loy = min(a.y, b.y), hiy = max(a.y, b.y);
        return x >= lox && x <= hix && y >= loy && y <= hiy;
    }
    // cross product magnitude of axb, relative to this
    T cross(const _Point &a, const _Point &b) const {
        return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x);
    }
};

typedef _Point<int> Point;


Point circ;
int r;
Point rect[4];



const char *outfile = "graph.tex";
FILE *out;

void tikz_header()
{
	out = fopen(outfile, "w");
	fprintf(out,
"\\documentclass[10pt]{article}\n"
"\\usepackage[paperwidth=15cm,paperheight=15cm]{geometry}\n"
"\\usepackage{tikz}\n"
"\\begin{document}\n");
}

int tikn = 0;
void tikz_case()
{
	fprintf(out,
"\n\\pagebreak\n"
"Case %d:\\\\\n"
"\\begin{tikzpicture}[scale=.3]\n"
"  \\draw[style=help lines] (0,0) grid (30, 30);\n"
"  \\draw[style=very thick] ", ++tikn);

	for (int i = 0; i < 4; ++i)
		fprintf(out, "(%d,%d) -- ", rect[i].x, rect[i].y);

	fprintf(out,
"cycle;\n"
"  \\draw[style=very thick] (%d,%d) circle(%d);\n"
"\\end{tikzpicture}\n", circ.x, circ.y, r);
}

void tikz_footer()
{
	fprintf(out,
"\\end{document}\n"
	);
	fclose(out);
}

void solve()
{
	rect[1] = Point(rect[2].x, rect[0].y);
	rect[3] = Point(rect[0].x, rect[2].y);

	tikz_case();
}

int main()
{
	int T;
	scanf("%d", &T);

	tikz_header();
	while (T--) {
		scanf("%d%d%d %d%d%d%d", &circ.x, &circ.y, &r,
		      &rect[0].x, &rect[0].y, &rect[2].x, &rect[2].y);

		solve();
	}
	tikz_footer();

	return 0;
}
