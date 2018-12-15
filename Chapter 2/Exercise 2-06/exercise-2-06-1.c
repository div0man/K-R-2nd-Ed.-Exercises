/* **Exercise 2-6.** Write a function `setbits(x,p,n,y)` that returns `x` with
 * the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`,
 * leaving the other bits unchanged.
 */

#include <stdio.h>

/* Left-aligned index, ie bits are counted as 01234567.
 * Example: p=2, n=3 gets us bits 234. */
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	/* set target bits in x to 0 */
	x &= ~(~0u >> p & ~(~0u >> (p + n - 1) >> 1));
	/* get the rightmost `n` bits of `y` and put them at the correct position */
	y &= ~(~0u << (n - 1u) << 1u);
	for (unsigned i = 0u; i < n; ++i) {
		if (y & 1u) {
			y >>= 1u;
			y |= ~(~0u >> 1u);
		}
		else {
			y >>= 1u;
		}
	}
	y >>= p;
	/* write the bits into x */
	x |= y;
	return x;
}

int main(void)
{
	unsigned x = 0x00000000;
	unsigned y = 0xFFFFFFFF;
	printf("0x%08X\n", setbits(x, 0, 32, y));
}
