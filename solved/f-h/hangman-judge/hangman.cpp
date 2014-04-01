#include <cstdio>
#include <cstring>


#define MAXLEN 1024

#define Clr(m) memset(m, 0, sizeof(m))


int round;
char sol[MAXLEN];
char gss[MAXLEN];

bool vis[26];
bool insol[26];


void solve()
{
	Clr(vis);
	Clr(insol);

	int letters = 0;

	int len_sol = strlen(sol);
	for (int i = 0; i < len_sol; ++i) {
		int idx = sol[i] - 'a';
		if (insol[idx]) continue;
		insol[idx] = true;
		++letters;
	}

	int good = 0, bad = 0;

	int len_gss = strlen(gss);
	for (int i = 0; i < len_gss; ++i) {
		int idx = gss[i] - 'a';
		if (vis[idx]) continue;
		vis[idx] = true;

		if (insol[idx]) {
			if (++good == letters) {
				puts("You win.");
				return;
			}
		}
		else {
			if (++bad == 7) {
				puts("You lose.");
				return;
			}
		}
	}
	puts("You chickened out.");
}

int main()
{
	while (true) {
		scanf("%d", &round);
		if (round == -1) break;

		scanf("%s%s", sol, gss);
		printf("Round %d\n", round);
		solve();
	}

	return 0;
}
