#include <cstdio>


#define MAXN 100000
#define MAXX 100000


struct Team {
	int h, a;
};


int n;
int home[MAXX+1];

Team teams[MAXN];


int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &teams[i].h, &teams[i].a);

		++home[teams[i].h];
	}

	for (int i = 0; i < n; ++i) {
		int h = n-1 + home[teams[i].a];
		int a = n-1 - home[teams[i].a];
		printf("%d %d\n", h, a);
	}

	return 0;
}
