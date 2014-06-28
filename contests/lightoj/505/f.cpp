/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem F: Molux Terminal Emulator
 *
 * Keywords:
 *   - simulation
 */

#include <cstdio>
#include <string>
using namespace std;


struct Dir {
	int id, parent;
	string name;
};

Dir fs[16];
int ndirs;


void prepare()
{
	fs[ndirs++] = (Dir) { 0, 0, "" };
	fs[ndirs++] = (Dir) { 1, 0, "etc" };
	fs[ndirs++] = (Dir) { 2, 0, "dev" };
	fs[ndirs++] = (Dir) { 3, 0, "home" };
	fs[ndirs++] = (Dir) { 4, 0, "usr" };
	fs[ndirs++] = (Dir) { 5, 0, "var" };
	fs[ndirs++] = (Dir) { 6, 3, "jono" };
	fs[ndirs++] = (Dir) { 7, 3, "mako" };
	fs[ndirs++] = (Dir) { 8, 3, "cory" };
	fs[ndirs++] = (Dir) { 9, 4, "lib" };
	fs[ndirs++] = (Dir) { 10, 6, "work" };
	fs[ndirs++] = (Dir) { 11, 6, "photos" };
}


int ninst;
int ptr;
char dir[1024];


void print_path_rec(int node)
{
	if (node == 0) return;

	print_path_rec(fs[node].parent);
	printf("/%s", fs[node].name.c_str());
}

void print_path(int node)
{
	if (node == 0) { puts("/"); return; }
	print_path_rec(node);
	putchar('\n');
}

void process(const string &dir)
{
	if (dir == "..") {
		ptr = fs[ptr].parent;
		print_path(ptr);
		return;
	}

	for (int i = 0; i < ndirs; ++i)
		if (fs[i].name == dir && fs[i].parent == ptr) {
			ptr = fs[i].id;
			print_path(ptr);
			return;
		}

	puts("No such file or directory");
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &ninst);

		ptr = 0;
		for (int i = 1; i <= ninst; ++i) {
			scanf(" cd %s", dir);
			printf("Case %d: ", i);
			process(dir);
		}
	}

	return 0;
}
