//
// Basic floating point utils
//
typedef double GeomT;

bool eqz(GeomT x) { return fabs(x) < EPS; }
GeomT sanitize(GeomT x) { return eqz(x) ? 0.0 : x; }
int cmp(GeomT a, GeomT b)
{
	GeomT s; if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

// for integers
#define eqz(x)   ((x) == 0)
#define cmp(a,b) ((a) - (b))


//
// Basic geometry
//

GeomT circle_angle(GeomT a) { return (a=sanitize(a)) >= 0.0 ? a : a+pi_t2; }

// Area of triangle with sides a, b, c
GeomT heron(GeomT a, GeomT b, GeomT c)
{
	GeomT s = (a + b + c) / 2.0;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Triangle's angle A - the opposite of side a
GeomT triangle_opp_angle(GeomT a, GeomT b, GeomT c)
{
	return acos((b*b + c*c - a*a) / (b * c * 2));
}


//
// 2D Data Types
//
struct Point {
	GeomT x, y;
	Point() {}
	Point(GeomT X, GeomT Y): x(X), y(Y) {}

	void dbg() const { printf("P(%d, %d)", x, y); }

	GeomT norm() const { return sqrt(x*x + y*y); }

	GeomT distance(const Point &p) const {
		GeomT dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy); }

	bool is_collinear(const Point &a, const Point &b) const {
		return eqz(cross(a, b)); }

	bool in_box(const Point &a, const Point &b) const {
		GeomT lox = min(a.x, b.x), hix = max(a.x, b.x);
		GeomT loy = min(a.y, b.y), hiy = max(a.y, b.y);
		return cmp(lox, x) <= 0 && cmp(x, hix) <= 0 &&
			cmp(loy, y) <= 0 && cmp(y, hiy) <= 0;
	}

	bool is_between(const Point &a, const Point &b) const {
		return is_collinear(a, b) && in_box(a, b); }

	// Returns a point between {this}-{p}, according to {r} (0: this, 1: p)
	Point interpolate(const Point &p, GeomT r) const {
		GeomT dx = p.x - x, dy = p.y - y;
		return Point(x + r*dx, y + r*dy);
	}

	// cross product magnitude of {a}x{b}, relative to {this}
	GeomT cross(const Point &a, const Point &b) const {
		return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x); }

	// {v} cross {this}, as vectors
	GeomT cross(const Point &v) const { return x * v.y  - y * v.x; }

	// signed angle
	GeomT sangle(const Point &p) const {
		return atan2(x*p.y - y*p.x, x*p.x + y*p.y); }

	GeomT angle(const Point &p) const { return circle_angle(sangle(p)); }

	void rotate(double a) {
		GeomT px = x, py = y;
		x = px*cos(a) - py*sin(a);
		y = px*sin(a) + py*cos(a);
	}

	// Distance between the line that passes through {a} with direction
	// {this}, and point {p}
	GeomT distance_line_point(const Point &a, const Point &p) const {
		return Abs((p.x-a.x)*y - (p.y-a.y)*x) / sqrt(x*x + y*y);
	}

	//
	// Operators
	//
	bool operator<(const Point &p) const {
		int c = cmp(x, p.x);
		if (c != 0) return c < 0;
		return cmp(y, p.y) < 0;
	}
	bool operator==(const Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }
	Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
};

typedef Point Vector;

struct Line {
	GeomT a, b, c;	// ax + by + c = 0
	Line(GeomT A, GeomT B, GeomT C): a(A), b(B), c(C) {}

	Line(const Point &p1, const Point &p2) {
		if (p1.x == p2.x) { a = 1, b = 0, c = -p1.x; return; }
		a = p1.y-p2.y; b = p2.x-p1.x; c = -a*p1.x - b*p1.y;
	}
	Line(const Point &p, GeomT m) { a = -m; b = 1; c = m*p.x - p.y; }

	bool is_parallel(const Line &l) const { return a * l.b == b * l.a; }
	bool is_vertical() const { return b == 0; }
	bool is_horizontal() const { return a == 0; }
	bool operator==(const Line &l) const {
		return is_parallel(l) && a * l.c == c * l.a;
	}
	bool intersection(const Line &l, Point &p) const {
		if (is_parallel(l)) return false;
		const Line &rl = is_vertical() ? l : *this;
		p.x = (l.b*c - b*l.c) / (l.a*b - a*l.b);
		p.y = -(rl.a * p.x + rl.c) / rl.b;
		return true;
	}
	Point closest_to(const Point &p) {
		if (is_vertical()) return Point(-c, p.y);
		if (is_horizontal()) return Point(p.x, -c);
		Point ans;
		intersection(Line(p, 1/a), ans);
		return ans;
	}
};


struct Segment {
	Point a, b;
	Segment(Point A, Point B) : a(A), b(B) {}

	void dbg() const {
		printf("Seg( "); a.dbg(); printf(","); b.dbg(); printf(" )"); }

	bool intersection(const Segment &s, Point &p) const {
		Line l1(a, b);
		Line l2(s.a, s.b);
		if (! l1.intersection(l2, p)) return false;
		return p.in_box(a, b) && p.in_box(s.a, s.b);
	}
};


struct Circle {
	GeomT x, y, r;
	Circle() {}
	Circle(GeomT X, GeomT Y, GeomT R): x(X), y(Y), r(R) {}

	// Finds the circle formed by three points
	Circle(const Point &p1, const Point &p2, const Point &p3) {
		Point m, a, b;
		if (! eps_equal(p1.x, p2.x) && ! eps_equal(p1.x, p3.x))
			m = p1, a = p2, b = p3;
		else if (! eps_equal(p2.x, p1.x) && ! eps_equal(p2.x, p3.x))
			m = p2, a = p1, b = p3;
		else
			m = p3, a = p1, b = p2;

		GeomT ma = (m.y - a.y) / (m.x - a.x);
		GeomT mb = (b.y - m.y) / (b.x - m.x);

		x = ma*mb*(a.y - b.y) + mb*(a.x + m.x) - ma*(m.x + b.x);
		x /= (mb - ma)*2.0;

		if (eps_equal(0.0, ma))
			y = (m.y + b.y) / 2.0 - (x - (m.x + b.x)/2.0) / mb;
		else
			y = (a.y + m.y) / 2.0 - (x - (a.x + m.x)/2.0) / ma;

		r = p1.distance(Point<T>(x, y));
	}
	GeomT circum() const { return pi * r * 2; }
	bool perimeters_touch(const Circle &c) const {
		double dx = x - c.x;
		double dy = y - c.y;
		double dist = sqrt(dx*dx + dy*dy);
		return ! (eps_less(r + c.r, dist) ||
				  eps_less(dist, fabs(r - c.r)));
	}

	void tangentPoints(const Point &p, Point &p1, Point &p2) {
		GeomT pox = x - p.x;
		GeomT poy = y - p.y;
		GeomT h2 = pox*pox + poy*poy;
		GeomT s = sqrt(h2 - r*r);
		p1 = Point(p.x + s*(pox*s-poy*r)/h2, p.y + s*(poy*s+pox*r)/h2);
		p2 = Point(p.x + s*(pox*s+poy*r)/h2, p.y + s*(poy*s-pox*r)/h2);
	}

	// Finds points of intersection with a line segment ab. If there is a
	// point "entering", uset will be true and u will be set. If there is a
	// point "exiting", vset will be true, and v will be set. Returns true
	// if a and b are both inside the circle.
	bool intersect_with_segment(
		const Point &a, const Point &b, bool &uset, Point &u,
		bool &vset, Point &v) const {
		uset = vset = false;

		GeomT A = (b.x-a.x) * (b.x-a.x) + (b.y - a.y) * (b.y - a.y);
		GeomT B = ((b.x-a.x) * (a.x-x) + (b.y - a.y) * (a.y - y))*2;
		GeomT C = x*x + y*y + a.x*a.x + a.y*a.y - 2*(x*a.x + y*a.y) - r*r;

		GeomT disc = B*B - 4*A*C;
		if (cmp(disc, 0) <= 0) return false;

		GeomT e = sqrt(disc);
		GeomT u1 = (-B + e) / (2*A);
		GeomT u2 = (-B - e) / (2*A);

		int u1_0 = cmp(u1, 0), u1_1 = cmp(u1, 1);
		int u2_0 = cmp(u2, 0), u2_1 = cmp(u2, 1);

		if ((u1_0 < 0 && u2_0 < 0) || (u1_1 > 0 && u2_1 > 0)) return false;
		if ((u1_0 < 0 || u1_1 > 0) && (u2_0 < 0 || u2_1 > 0)) return true;

		if (u2_0 >= 0 && u2_1 <= 0)
			u = a.interpolate(b, u2), uset = true;
		if (u1_0 >= 0 && u1_1 <= 0)
			v = a.interpolate(b, u1), vset = true;

		// if uset && vset && u == v, the segment is tangent
		return false;
	}

	// (signed) area of intersection with a triangle anchored on the
	// circle's center
	GeomT area_with_atriangle(const Point &a, const Point &b) const {
		Point u, v; bool us, vs;
		bool inside = intersect_with_segment(a, b, us, u, vs, v);

		Point c(x, y);
		if (inside) return c.cross(a, b) / 2;
		if (! us && ! vs) {
			Vector av = a-c, bv = b-c;
			return av.sangle(bv)/2 * r*r;
		}
		GeomT ans = 0;
		if (us) {
			Vector av = a-c, uv = u-c;
			ans += av.sangle(uv)/2 * r*r;
		}
		else ans += c.cross(a, v) / 2;

		if (vs) {
			Vector vv = v-c, bv = b-c;
			ans += vv.sangle(bv)/2 * r*r;
		}
		else ans += c.cross(u, b) / 2;

		if (us && vs) ans += c.cross(u, v) / 2;
		return ans;
	}

	// (signed) area of intersection with an arbitrary polygon
	GeomT area_with_poly(Point *poly, int n) const {
		GeomT a = 0;
		for (int i = 0, j = n - 1; i < n; j = i++)
			a += area_with_atriangle(poly[j], poly[i]);
		return a;
	}
};


// cross product magnitude of axb, relative to (0,0)
GeomT cross(const Point &a, const Point &b)
{
	return a.x*b.y - a.y*b.x;
}
// returns the sign of the cross product
GeomT cross_sgn(const Point &a, const Point &b)
{
	double c = sanitize(cross(a, b));
	return c == 0.0 ? c : c / Abs(c);
}

// area of a polygon, times two
GeomT poly_area_t2(Point *p, int n)
{
	GeomT a = 0;
	for (int i = 0, j = n - 1; i < n; j = i++)
		a += (p[j].x + p[i].x) * (p[j].y - p[i].y);
	return a < 0 ? -a : a;
}

// check if point {p} is inside the polygon {poly} with {n} vertices
bool is_inside_poly(const Point &p, Point *poly, int n)
{
	int cnt = 0;
	for (int u = n - 1, v = 0; v < n; u = v++) {
		Point *a = &poly[u];
		Point *b = &poly[v];

		if (p.is_collinear(*a, *b) && p.in_box(*a, *b)) return true;
		if (p.cross(*a, *b) < 0) swap(a, b);
		if (a->y >= p.y && b->y < p.y) ++cnt;
	}
	return cnt % 2 != 0;
}

// counts the number of lattice points between {a} and {b}
int lattice_pts(const Point &a, const Point &b)
{
	if (a.x == b.x) return llabs(a.y - b.y) + 1;
	return gcd(llabs(a.y - b.y), llabs(a.x - b.x)) + 1;
}

void convex_hull(Point *p, int n, Point *h, int &k) {
	// Pre-cond:  sizeof(h) == 2*sizeof(p)
	// Post-cond: n > 1 => h[0] == h[k-1]
	k = 0;
	sort(p, p + n);
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	for (int i = n-2, t=k+1; i >= 0; --i) {
		while (k >= t && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
}


//
// 3D Data types
//
struct Point3D {
	GeomT x, y, z;

	Point3D() {}
	Point3D(GeomT X, GeomT Y, GeomT Z): x(X), y(Y), z(Z) {}

	void dbg() const {
		printf("P(%.2lf, %.2lf, %.2lf)", x, y, z);
	}

	bool is_zero() const { return eqz(x) && eqz(y) && eqz(z); }
	Point3D cross(const Point3D &p) const {
		return Point3D(
			y * p.z - z * p.y,
			-x * p.z + z * p.x,
			x * p.y - y * p.x);
	}
	GeomT dot(const Point3D &p) const { return x * p.x + y * p.y + z * p.z; }
	GeomT norm() const { return sqrt(x*x + y*y + z*z); }

	Point3D &operator+=(const Point3D &p) {
		x += p.x, y += p.y, z += p.z; return *this; }
	Point3D &operator-=(const Point3D &p) {
		x -= p.x, y -= p.y, z -= p.z; return *this; }
	Point3D &operator*=(GeomT s) {
		x *= s, y *= s, z *= s; return *this; }

	Point3D operator+(const Point3D &p) const {
		Point3D ans = *this; ans += p; return ans; }
	Point3D operator-(const Point3D &p) const {
		Point3D ans = *this; ans -= p; return ans; }
	Point3D operator*(GeomT s) const {
		Point3D ans = *this; ans *= s; return ans; }
};

typedef Point3D Vector3D;

struct Ray3D {
	Point3D p0, p1;

	Ray3D() {}
	Ray3D(Point3D P0, Point3D P1): p0(P0), p1(P1) {}

	void dbg() const {
		printf("Ray("); p0.dbg(); printf(" - "); p1.dbg(); printf(")");
	}
};

struct Triangle3D {
	Point3D v0, v1, v2;

	Triangle3D() {}
	Triangle3D(Point3D V0, Point3D V1, Point3D V2): v0(V0), v1(V1), v2(V2) {}

	void dbg() const {
		printf("Tri("); v0.dbg(); printf(", ");
		v1.dbg(); printf(", ");
		v2.dbg(); printf(")");
	}

	bool intersect_ray(const Ray3D &ray, Point3D &it) {
		Vector3D u = v1 - v0;
		Vector3D v = v2 - v0;
		Vector3D n = u.cross(v);

		// triangle is degenerate
		if (n.is_zero()) return false;

		Vector3D dir = ray.p1 - ray.p0;
		Vector3D w0 = ray.p0 - v0;
		GeomT a = - n.dot(w0);
		GeomT b = n.dot(dir);

		// if a == 0 -> ray lies in plane, else ray is disjoint from plane
		if (eqz(b)) return false;

		GeomT r = a / b;
		if (r < 0)
			return false;  // ray is going away from the triangle
		// for a segment, also test if (r > 1.0) => no intersect
		it = ray.p0 + dir * r;

		Vector3D w = it - v0;
		GeomT uu = u.dot(u);
		GeomT uv = u.dot(v);
		GeomT vv = v.dot(v);
		GeomT wu = w.dot(u);
		GeomT wv = w.dot(v);
		GeomT D = uv * uv - uu * vv;

		GeomT s = (uv * wv - vv * wu) / D;
		if (s < 0.0 || s > 1.0) return false;

		GeomT t = (uv * wu - uu * wv) / D;
		if (t < 0.0 || (s + t) > 1.0) return false;

		// if s == 0 || t == 0 || s+t == 1.0 then point lies on an edge
		return true;
	}

};
