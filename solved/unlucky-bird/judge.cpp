/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// 0 AC
// 1 WA
// 2 PE

// output format 'Case %d: %lf %lf'

bool getDouble2( char *a, int &i, double &d1, double &d2 ) {
	if( strlen(a) - i > 50 ) return 0.0;
	int k = 0;
	char x[100], y[100], z[100], z1[100];
	for( ; a[i] && a[i] != ' '; i++ ) x[k++] = a[i];
	x[k] = 0;
	if( a[i] != ' ' ) return false;
	if( a[++i] == ' ' ) return false;
	k = 0;
	for( ; a[i] && a[i] != '\n' && a[i] != ' '; i++ ) y[k++] = a[i];
	y[k] = 0;
	if( a[i] != '\n' ) return false;

	if( sscanf(y, "%s %s", z1, z) == 2 ) return false;

	if( sscanf(x, "%lf", &d1) == 1 && sscanf(y, "%lf", &d2) == 1 ) {
		if( isnan( d1 ) || isnan( d2 ) ) return false;
		return true;
	}
	return false;
}

int checkAc( FILE *pu, FILE *pj ) {
	char au[100], aj[100];

	while( fgets( aj, 100, pj ) ) {
		if( !fgets( au, 100, pu ) ) return 1;

		int i = 0, j = 0;
		while( aj[j] && aj[j] != ':' ) j++;
		while( au[i] && au[i] != ':' ) i++;

		if( au[i] != ':' ) return 1;

		au[i] = 0;
		aj[j] = 0;
		if( strcmp( au, aj ) ) return 1;
		au[i] = ':';

		if( au[++i] != ' ' ) return 1;
		if( au[++i] == ' ' ) return 1;
		double d1, d2;
		if( !getDouble2( au, i, d1, d2 ) ) return 1;

		double d3, d4;
		sscanf( aj+j+1, "%lf %lf", &d3, &d4 );

		if( fabs(d1-d3) > 1e-6 || fabs(d2-d4) > 1e-6 ) return 1;
	}
	if( fgets( au, 100, pu ) ) return 1;
	return 0;
}

int checkPe( FILE *pu, FILE *pj ) {
	char x[100];
	char au[100], aj[100];
	int caseno1, caseno2;
	double res1, res2, res3, res4;

	while( fscanf( pj, " Case %d : %lf %lf", &caseno1, &res1, &res2 ) == 3 ) {
		if( fscanf( pu, " Case %d : %lf %lf", &caseno2, &res3, &res4 ) == 3 ) {
			if( isnan( res3 ) || isnan( res4 ) ) return 1;
			if( fabs(res1-res3) > 1e-6 || fabs(res2-res4) > 1e-6 || caseno1 != caseno2 ) return 1;
		}
		else return 1;
	}
	if( fscanf( pu, "%s", x ) == 1 ) return 1;
	return 2;
}

int main( int argc, char *argv[] ) {
	char
		*inputFile,
		*answerFileU,
		*answerFileJ;

	int status;

	inputFile = argv[1];
	answerFileU = argv[2];
	answerFileJ = argv[3];

	FILE *pu, *pj;

	pu = fopen( answerFileU, "r" );
	pj = fopen( answerFileJ, "r" );
	status = checkAc( pu, pj );
	fclose(pu);
	fclose(pj);

	if( status == 1 ) {
		pu = fopen( answerFileU, "r" );
		pj = fopen( answerFileJ, "r" );
		status = checkPe( pu, pj );
		fclose(pu);
		fclose(pj);
	}

	if( status == 0 ) puts("AC");
	else if( status == 2 ) puts("PE");
	else puts("WA");

	return 0;
}

