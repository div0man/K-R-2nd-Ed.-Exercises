/* Exercise 2-3. Write the function `htoi(s)` which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value.The allowable digits are 0 through 9, a through f, and A
 * through F.
 */

#include <stdio.h>
#include <ctype.h>

#define HTOISAFE
#ifdef HTOISAFE
#include <limits.h>
#endif

/* Converts a string of hexadecimal digits (including an optional 0x or 0X) into
 * its equivalent integer value. Ignores leading whitespace and any trailing
 * garbage. Returns 0 for empty strings. Undefined for NULL. Undefined for 
 * overly big numbers unless HTOISAFE is defined. */
int htoi(const char *s);

int main(void)
{
	char str[]="      0x1234 garbage 123";
	printf("%i\n", htoi(str));
	return 0;
}

/* helper function, returns integer value of a hexadecimal char constant */
int hctoi(char c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else if (c >= '0' && c <= '9')
		return c - '0';
	else
		return -1;
}

int htoi(const char *s)
{
	/* find index of the first digit, exit if none found */
	size_t ind = 0;
	while (isspace(s[ind]))
		++ind;
	if (!isxdigit(s[ind])) {
		return 0;
	}
	else if (s[ind] == '0' && (s[ind+1] == 'x' || s[ind+1] == 'X') &&
			isxdigit(s[ind+2])) {
		ind += 2;
	}
	/* compute the resulting integer */
	int res = 0;
#ifndef HTOISAFE
	/* unsafe fast version, result undefined for too big numbers */
	for (; isxdigit(s[ind]); ++ind)
		res = 16*res + hctoi(s[ind]);
	return res;
#else
	/* safe version, computes up to INT_MAX */
	size_t tail;
	for (tail = ind; isxdigit(s[tail+1]); ++tail)
		;
	int exp = 1;
	while (ind < tail && exp < INT_MAX/16) {
		res += hctoi(s[tail]) * exp;
		--tail;
		exp *= 16;
	}
	if (hctoi(s[tail]) <= 7)
		res += hctoi(s[tail]) * exp;
	else
		res += 7 * exp;
	return res;
#endif
}
