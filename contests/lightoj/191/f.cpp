#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define INF 210.0
#define EPS (1e-9)

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

bool eps_less(double a, double b)
{
    return b - a > EPS;
}

bool eps_equal(double a, double b)
{
    return fabs(a - b) < EPS;
}

typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(Point p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
};

typedef vector<Point> PV;

double best;

bool circle_enclose(Point &c, double r, PV &pts)
{
    cFor (PV, p, pts)
        if (eps_less(r, c.distance(*p))) return false;
    return true;
}

void find_circle(Point &p1, Point &p2, Point &p3, Point &c, double &r)
{
    Point m, a, b;
    if (! eps_equal(p1.x, p2.x) && ! eps_equal(p1.x, p3.x))
        m = p1, a = p2, b = p3;
    else if (! eps_equal(p2.x, p1.x) && ! eps_equal(p2.x, p3.x))
        m = p2, a = p1, b = p3;
    else
        m = p3, a = p1, b = p2;

    double ma = (m.y - a.y) / (m.x - a.x);
    double mb = (b.y - m.y) / (b.x - m.x);

    c.x = ma*mb*(a.y - b.y) + mb*(a.x + m.x) - ma*(m.x + b.x);
    c.x /= (mb - ma)*2.0;

    if (eps_equal(0.0, ma))
        c.y = (m.y + b.y) / 2.0 - (c.x - (m.x + b.x)/2.0) / mb;
    else
        c.y = (a.y + m.y) / 2.0 - (c.x - (a.x + m.x)/2.0) / ma;

    r = c.distance(p1);
}

double min_diameter(PV &p)
{
    int sz = p.size();

    double R = INF;
    Point C;

    // Consider all pairs
    for (int i = 0; i < sz; ++i)
        for (int j = i + 1; j < sz; ++j) {
            Point c = Point((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
            double r = c.distance(p[i]);

            if (circle_enclose(c, r, p) && r < R)
                R = r, C = c;
        }

    // Consider all groups of three points
    for (int i = 0; i < sz; ++i)
        for (int j = i + 1; j < sz; ++j)
            for (int k = j + 1; k < sz; ++k) {
                if (p[i].collinear(p[j], p[k])) {
//                    printf("  coll...\n");
                    continue;
                }

                Point c;
                double r;
                find_circle(p[i], p[j], p[k], c, r);

//                printf("  found circle (%lf, %lf) %lf  with R(%lf)\n", c.x, c.y, r, R);
                if (circle_enclose(c, r, p) && r < R)
                    R = r, C = c;
            }

//    printf("  -- The best circle is (%lf, %lf) %lf\n", C.x, C.y, R);
    return R*2.0;
}

void print_result(double d)
{
    if (d <= 5.0)
        printf("Marksman %.1lf\"\n", d);
    else if (d <= 10.0)
        printf("Grouping %.1lf\"\n", d);
    else
        puts("Washed Out");
}

void process_firer()
{
    PV pts;

    for (int i = 0; i < 5; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        pts.push_back(Point(x, y));
    }

    double d = min_diameter(pts);

    if (d < best) best = d;
    print_result(d);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        if (ncase > 0) puts("");

        printf("Group %d:\n", ++ncase);

        best = INF;
        for (int i = 0; i < 8; ++i)
            process_firer();

        printf("Best: ");
        print_result(best);
    }

    return 0;
}
