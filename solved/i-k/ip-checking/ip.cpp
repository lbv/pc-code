#include <cstdio>


#define MAXLEN 64


char ip1s[MAXLEN];
char ip2s[MAXLEN];

int ip1[4], ip2[4];


void parse_bin_ip(const char *s, int &ip)
{
	ip = 0;
	for (int i = 0; i < 8; ++i) {
		ip <<= 1;
		if (s[i] == '1') ++ip;
	}
}

bool solve()
{
	sscanf(ip1s, "%d.%d.%d.%d", &ip1[0], &ip1[1], &ip1[2], &ip1[3]);

	for (int i = 0; i < 4; ++i) parse_bin_ip(ip2s + i*9, ip2[i]);

	for (int i = 0; i < 4; ++i) if (ip1[i] != ip2[i]) return false;

	return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s%s", ip1s, ip2s);
		printf("Case %d: ", ++ncase);

		if (solve())
			puts("Yes");
		else
			puts("No");
	}

	return 0;
}
