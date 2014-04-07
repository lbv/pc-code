#include <cstdio>
#include <map>
#include <vector>
using namespace std;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef vector<int> VI;


VI uniq_list;
map<int, int> count;


int main()
{
	int num;
	while (true) {
		if (scanf("%d", &num) != 1) break;

		if (++count[num] == 1)
			uniq_list.push_back(num);
	}

	For (VI, n, uniq_list)
		printf("%d %d\n", *n, count[*n]);

	return 0;
}
