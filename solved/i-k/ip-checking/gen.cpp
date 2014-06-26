#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100


int T;
int ip[4];
char ips[16];


void gen_ip()
{
	for (int i = 0; i < 4; ++i)
		ip[i] = rand() % 256;
}

void rand_bin_ip()
{
	for (int i = 0; i < 8; ++i)
		ips[i] = rand() % 2 == 0 ? '0' : '1';
}

void alter_bin_ip()
{
	for (int i = 0; i < 8; ++i)
		if (rand() % 10 == 0)
			ips[i] = ips[i] == '0' ? '1' : '0';
}

void dec_to_bin(int ip)
{
	for (int i = 0; i < 8; ++i)
		ips[7-i] = (ip & (1 << i)) ? '1' : '0';
}

void gen()
{
	gen_ip();

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		printf("%d", ip[i]);
	}
	putchar('\n');

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		dec_to_bin(ip[i]);
		printf("%s", ips);
	}
	putchar('\n');

	--T;
}

void gen_close()
{
	gen_ip();

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		printf("%d", ip[i]);
	}
	putchar('\n');

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		dec_to_bin(ip[i]);
		alter_bin_ip();
		printf("%s", ips);
	}
	putchar('\n');

	--T;
}

void gen_rand()
{
	gen_ip();

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		printf("%d", ip[i]);
	}
	putchar('\n');

	for (int i = 0; i < 4; ++i) {
		if (i > 0) putchar('.');
		rand_bin_ip();
		printf("%s", ips);
	}
	putchar('\n');

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) {
		int r = rand() % 3;

		if (r == 0) gen_close();
		else if (r == 1) gen_rand();
		else gen();
	}

	return 0;
}
