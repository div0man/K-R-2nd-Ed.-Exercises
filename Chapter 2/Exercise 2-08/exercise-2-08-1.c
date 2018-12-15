/* **Exercise 2-8.** Write a function `rightrot(x,n)` that returns the value of
 * the integer `x` rotated to the right by `n` bit positions.
 */

#include <stdio.h>

/* Right-aligned index, i.e. bits are counted as 76543210.
 * Example: p=4, n=3 gets us bits 432. */
unsigned rightrot(unsigned x, unsigned n)
{
	for (unsigned i = 0u; i < n; ++i) {
		if (x & 1u) {
			x >>= 1u;
			x |= ~(~0u >> 1u);
		}
		else {
			x >>= 1u;
		}
	}
	return x;
}


int main(void)
{
	unsigned x = 0xFFFFFF11;
	printf("0x%08X\n", rightrot(x, 48));
}
