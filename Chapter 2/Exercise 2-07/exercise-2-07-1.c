/* **Exercise 2-7.** Write a function `invert(x,p,n) that returns `x` with the
 * `n` bits that begin at position `p` inverted (i.e., 1 changed into 0 and
 * vice versa), leaving the others unchanged.
 */

#include <stdio.h>

/* Right-aligned index, ie bits are counted as 76543210.
 * Example: p=4, n=3 gets us bits 432. */
unsigned invert(unsigned x, unsigned p, unsigned n)
{
	unsigned mask;
	/* set target bits in mask to 1 */
	mask = ~(~0u << (n - 1u) << 1u) << ~(~0u << (p - n + 1u));
	/* XOR the mask over x */
	x ^= mask;
	return x;
}


int main(void)
{
	unsigned x = 0xFFFFFF11;
	printf("0x%08X\n", invert(x, 31, 32));
}
