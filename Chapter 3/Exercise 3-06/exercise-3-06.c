/* **Exercise 3-6.** Write a version of `itoa` that accepts three arguments
 * instead of two. The third argument is a minimum field width; the converted
 * number must be padded with blanks on the left if necessary to make it wide
 * enough.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[], int fw);
size_t getline(char *s, size_t sz);
void reverse(char *s);

int main(void)
{
	char s[16];
	int fw = 8;
	int n;

	n = INT_MAX;
	itoa(n, s, fw);
	printf("<%8d>\n<%s>\n\n", n, s);

	n = INT_MIN;
	itoa(n, s, fw);
	printf("<%8d>\n<%s>\n\n", n, s);

	n = 123;
	itoa(n, s, fw);
	printf("<%8d>\n<%s>\n\n", n, s);

	n = -123;
	itoa(n, s, fw);
	printf("<%8d>\n<%s>\n\n", n, s);
}

/* itoa: convert n to characters in s, using a minimum field width fw */
/* modified to work with INT_MIN & pad the number up to specified field width */
void itoa(int n, char s[], int fw)
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
	while (i < fw)
		s[i++] = ' ';
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
