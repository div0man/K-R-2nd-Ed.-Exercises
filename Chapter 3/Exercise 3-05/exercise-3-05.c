/* **Exercise 3-5.** Write the function `itob(n,s,b)` that converts the integer
 * `n` into a base `b` character representation in the string `s`. In
 * particular, `itob(n,s,16)` formats `s` as a hexadecimal integer in `s`.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

void itob(int n, char *s, int b);
void reverse(char *restrict s);

int main(void)
{
	char s[50];
	int n, b;

	n = INT_MAX;
	b = 2;
	itob(n, s, b);
	printf("%d\t%x\t%o\t%s\n", n, n, n, s);

	n = INT_MIN;
	itob(n, s, b);
	printf("%d\t%x\t%o\t%s\n", n, n, n, s);

	n = 123;
	itob(n, s, b);
	printf("%d\t%x\t%o\t%s\n", n, n, n, s);

	n = -123;
	itob(n, s, b);
	printf("%d\t%x\t%o\t%s\n", n, n, n, s);
}

/* b must be between 2 and 36 */
void itob(int n, char *s, int b)
{
	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;
	int sign;

	/* deal with the edge case right away, special treatment for 1st digit */
	if (n == INT_MIN) {
		s[i++] = digits[(n % b) * (n % b < 0 ? -1 : 1)];
		n /= b;
	}

	/* record the sign and make n positive */
	if ((sign = n) < 0)
		n = -n;
	/* write the number in reverse */
	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}

/* reverse: reverse a '\0' terminated string in place
 */
void reverse(char *s)
{
	char c;
	for (size_t head = 0, tail = strlen(s)-1; head < tail; ++head, --tail) {
		c = s[head];
		s[head] = s[tail];
		s[tail] = c;
	}
}
