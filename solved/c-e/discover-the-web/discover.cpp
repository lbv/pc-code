#include <cstdio>
#include <cstring>


#define MAXSTK 100
#define MAXLEN 64


char cmd;
char url[MAXLEN];
char aurl[MAXLEN];  // active URL

char fk[MAXSTK][MAXLEN];  // forward stack
char bk[MAXSTK][MAXLEN];  // bacward stack
int ifk, ibk;


bool process_command()
{
	scanf(" %c%*s", &cmd);
	if (cmd == 'Q') return false;

	if (cmd == 'V') {
		scanf("%s", url);
		strcpy(bk[ibk++], aurl);
		strcpy(aurl, url);
		ifk = 0;
		puts(aurl);
	}
	else if (cmd == 'B') {
		if (ibk == 0) puts("Ignored");
		else {
			strcpy(fk[ifk++], aurl);
			strcpy(aurl, bk[--ibk]);
			puts(aurl);
		}
	}
	else if (cmd == 'F') {
		if (ifk == 0) puts("Ignored");
		else {
			strcpy(bk[ibk++], aurl);
			strcpy(aurl, fk[--ifk]);
			puts(aurl);
		}
	}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		ifk = ibk = 0;
		strcpy(aurl, "http://www.lightoj.com/");

		printf("Case %d:\n", ++ncase);
		while (process_command());
	}

	return 0;
}
