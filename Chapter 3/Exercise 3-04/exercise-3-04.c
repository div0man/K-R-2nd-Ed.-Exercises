/* **Exercise 3-4.** In a two's complement number representation, our version of
 * `itoa` does not handle the largest negative number, that is, the value of `n`
 * equal to -(2<sup>wordsize-1</sup>). Explain why not. Modify it to print that
 * value correctly, regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa_mod(int n, char s[]);
void itoa(int n, char s[]);
size_t getline(char *s, size_t sz);
void reverse(char *s);

int main(void)
{
	char s[16];

	printf("Original\n");
	int n = INT_MAX;
	itoa(n, s);
	printf("%d = <%s>\n", n, s);
	n = INT_MIN;
	itoa(n, s);
	printf("%d = <%s>\n", n, s);

	printf("Modified\n");
	n = INT_MAX;
	itoa_mod(n, s);
	printf("%d = <%s>\n", n, s);
	n = INT_MIN;
	itoa_mod(n, s);
	printf("%d = <%s>\n", n, s);
}

/* itoa: convert n to characters in s */
/* code copied from K&R page 64 */
void itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)		/* record sign */
		n = -n;				/* make n positive */
	i = 0;
	do {		/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* itoa_mod: convert n to characters in s */
/* modified to work with INT_MIN */
void itoa_mod(int n, char s[])
{
	int i = 0;
	/* deal with the edge case right away, special treatment for 1st digit */
	if (n == (int)~(~0u >> 1)) {
		s[i++] = (n % 10) * (n % 10 < 0 ? -1 : 1) + '0';
		n /= 10;
	}
	/* business as usual */
	int sign;
	if ((sign = n) < 0)		/* record sign */
		n = -n;				/* make n positive */
	do {		/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse string s in place */
/* code copied from K&R page 62 */
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
