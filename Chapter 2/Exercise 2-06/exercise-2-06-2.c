/* **Exercise 2-6.** Write a function `setbits(x,p,n,y)` that returns `x` with
 * the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`,
 * leaving the other bits unchanged.
 */

#include <stdio.h>

/* Right-aligned index, ie bits are counted as 76543210.
 * Example: p=4, n=3 gets us bits 432. */
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
	/* set target bits in x to 0 */
	x &= ~(~(~0u << (n - 1u) << 1u) << ~(~0u << (p - n + 1u)));
	/* get the rightmost `n` bits of `y` and put them at the correct position */
	y &= ~(~0u << (n - 1u) << 1u);
	y <<= (p - n + 1u);
	/* write the bits into x */
	x |= y;
	return x;
}

int main(void)
{
	unsigned x = 0x00000000;
	unsigned y = 0xFFFFFFFF;
	printf("0x%08X\n", setbits(x, 31, 32, y));
}
