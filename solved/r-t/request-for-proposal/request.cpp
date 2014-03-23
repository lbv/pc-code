#include <cstdio>
#include <cstring>


#define MAXN 1000
#define MAXSTR 82


struct Proposal {
	double d;
	int r;

	bool operator<(const Proposal &p) const {
		if (r != p.r) return r < p.r;
		return d > p.d;
	}
};


char pname[MAXSTR], pbest[MAXSTR];
int n, p;


int main()
{
	Proposal best, curr;

	int ncase = 0;
	while (true) {
		scanf("%d%d ", &n, &p);
		if (n == 0) break;

		best.r = 0;

		for (int i = 0; i < n; ++i)
			scanf("%*[^\n] ");

		for (int i = 0; i < p; ++i) {

			scanf("%[^\n]%lf%d ", pname, &curr.d, &curr.r);

			for (int j = 0; j < curr.r; ++j)
				scanf("%*[^\n] ");

			if (best < curr) {
				best = curr;
				strcpy(pbest, pname);
			}
		}

		if (ncase > 0) puts("");
		printf("RFP #%d\n%s\n", ++ncase, pbest);
	}

	return 0;
}
