#define PosLSB(x) (__builtin_ctzll(x))
#define GetLSB(x) ((x) & -(x))
#define ClrLSB(x) (x &= ~GetLSB(x))

#define PosMSB(x) (63 - __builtin_clzll(x))
#define GetMSB(x) (1ULL << PosMSB(x))

// Returns first integer with exactly n bits set
u32 popcnt_init(int n) { return (1 << n) - 1; }

// next higher number with same number of 1's in binary
u32 popcnt_next(u32 n)
{
	u32 c = (n & -n), r = n+c;
	return (((r ^ n) >> 2) / c) | r;
}


//
// Variants for non-gcc compilers
//

// values of (1 << x) for x<32 are unique modulo 37
static const int m37pos[] = {
	32,  0,  1, 26,  2, 23, 27,  0,  3,
	16, 24, 30, 28, 11,  0, 13,  4,  7,
	17,  0, 25, 22, 31, 15, 29, 10, 12,
	 6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define PosLSB(x) (m37pos[(x) % 37])

// Finds the most significant bit set on n. The bit is left in b, and its
// zero-indexed position in p
void msb(i64 n, i64 &b, int &p)
{
	for (b = 1, p = 0, n >>= 1; n; b <<= 1, n >>= 1, ++p);
}
