/*
	Author       :	Jan
	Problem Name :	Country Roads
	Algorithm    :	Input Generator
	Complexity   :
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

#define max(a,b) ((a) > (b) ? (a) : (b))

#define CLR(a) memset(a,0,sizeof(a))

#define MAX 501

int main()
{
	freopen("c.in","w",stdout);

	int cases=20,m,n,u,v,k;

	printf("%d\n", cases);
	while(cases--)
	{
		n = 500 - rand() % 5;
		while(1)
		{
			m=16000 - rand() % 10;
			if(m>=n*n) continue;
			break;
		}

		printf("\n%d %d\n",n,m);
		while(m--)
		{
			while(1)
			{
				u=rand()%n;
				v=rand()%n;
				if(u!=v) break;
			}
			k=rand() % 20000 + 1;

			printf("%d %d %d\n",u,v,k);
		}
		printf("%d\n",rand()%n);
	}
	return 0;
}

