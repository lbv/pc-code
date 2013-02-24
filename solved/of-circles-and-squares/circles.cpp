#include <cstdio>


#define MAXR 100
#define EPS  (1e-9)


struct Color {
    int r, g, b;
    Color() {}
    Color(int R, int G, int B) : r(R), g(G), b(B) {}
};

struct Circle {
    int x, y, r;
    int r2;
    Color c;
    Circle() {}
    Circle(int X, int Y, int R, Color C) : x(X), y(Y), r(R), c(C) {
        r2 = r*r;
    }
    bool is_outside(int px, int py) const {
        int dx = px - x, dy = py - y;
        return dx*dx + dy*dy > r2;
    }
    bool is_on_border(int px, int py) const {
        int dx = px - x, dy = py - y;
        return dx*dx + dy*dy == r2;
    }
};

struct Square {
    int x, y, l;
    Color c;
    Square() {}
    Square(int X, int Y, int L, Color C) : x(X), y(Y), l(L), c(C) {}
    bool is_outside(int px, int py) const {
        return px < x || px > x + l || py < y || py > y + l;
    }
    bool is_on_border(int px, int py) const {
        return
            ( py >= y && py <= y + l && (px == x || px == x + l) ) ||
            ( px >= x && px <= x + l && (py == y || py == y + l) );
    }
};


int R, P;
int nc, ns;  // number of circles and squares

Circle cirs[MAXR];
Square sqrs[MAXR];


void find_color(int x, int y, double &r, double &g, double &b)
{
    int shapes = 0;
    r = g = b = 0;

    for (int i = 0; i < nc; ++i) {
        if (cirs[i].is_outside(x, y)) continue;
        if (cirs[i].is_on_border(x, y)) {
            r = 0, g = 0, b = 0;
            return;
        }
        r += cirs[i].c.r;
        g += cirs[i].c.g;
        b += cirs[i].c.b;
        ++shapes;
    }
    for (int i = 0; i < ns; ++i) {
        if (sqrs[i].is_outside(x, y)) continue;
        if (sqrs[i].is_on_border(x, y)) {
            r = 0, g = 0, b = 0;
            return;
        }
        r += sqrs[i].c.r;
        g += sqrs[i].c.g;
        b += sqrs[i].c.b;
        ++shapes;
    }
    if (shapes == 0) {
        r = g = b = 255;
        return;
    }
    r /= shapes;
    g /= shapes;
    b /= shapes;
    r += EPS;
    g += EPS;
    b += EPS;
}

int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;
    int  ncase = 0;
    while (T--) {
        scanf("%d%d", &R, &P);
        nc = ns = 0;
        while (R--) {
            char obj[8];
            int x, y, l, r, g, b;
            scanf("%s%d%d%d%d%d%d", obj, &x, &y, &l, &r, &g, &b);

            Color col(r, g, b);
            if (obj[0] == 'C')
                cirs[nc++] = Circle(x, y, l, col);
            else
                sqrs[ns++] = Square(x, y, l, col);
        }

        if (first) first = false;
        else       putchar('\n');

        printf("Case %d:\n", ++ncase);
        while (P--) {
            int px, py;
            double r, g, b;
            scanf("%d%d", &px, &py);
            find_color(px, py, r, g, b);
            printf("(%.0lf, %.0lf, %.0lf)\n", r, g, b);
        }
    }

    return 0;
}
