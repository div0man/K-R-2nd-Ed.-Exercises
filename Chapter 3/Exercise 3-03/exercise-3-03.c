/* **Exercise 3-3.** Write a function `expand(s1,s2)` that expands shorthand
 * notations like `a-z` in the string `s1` into the equivalent complete list
 * `abc...xyz` in `s2`. Allow for letters of either case and digits, and be
 * prepared to handle cases like `a-b-c` and `a-z0-9` and `-a-z`. Arrange that a
 * leading or trailing - is taken literally.
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 256

void expand(char const * restrict s1, char * restrict s2);
size_t getline(char *s, size_t sz);

int main(void)
{
	char str[BUFSIZE];
	char exp[BUFSIZE * 16];
	size_t len;
	while ((len = getline(str, BUFSIZE)) > 0) {
		printf("Original=<%s>\n", str);
		expand(str, exp);
		printf("Expanded=<%s>\n", exp);
		for (size_t i = 0; i < BUFSIZE; ++i)
			exp[i] = (char)0xFE;
	}
}

void expand(char const * restrict s1, char * restrict s2)
{
	size_t prev = 0;
	size_t j = 0;
	for (size_t i = 0; s1[i] != '\0'; ++i, ++j) {
		/* entering potential pattern */
		if (s1[i] == '-' && isalnum(s1[prev])) {
			/* set allowable limits for the pattern closing char */
			char l = s1[prev];
			char h;
			if (l >= '0' && l <= '9')
				h = '9';
			else if (l >= 'a' && l <= 'z')
				h = 'z';
			else
				h = 'Z';
			/* get to the end of the pattern */
			while (s1[i] == '-' && s1[i+1] >= l && s1[i+1] <= h)
				l = s1[i+1], i += 2;
			/* if index got moved, means we have a valid closing char */
			if (prev+1 < i) {
				h = s1[--i];
				if (s1[prev] < h) {
					for (char c = (char)(s1[prev]+1); c < h; ++c)
						s2[j++] = c;
					s2[j] = h;
				}
				else {
					--j; /* x-x kind of patttern, pop the '-' */
				}
			}
			else {
				s2[j] = '-';
			}
		}
		else {
			s2[j] = s1[i];
		}
		prev = i;
	}
	s2[j] = '\0';
}

/* getline: read a line into `s`, return string length.
 * `sz` must be >1 to accomodate at least one character and '\0' terminator.
 * `sz = 0` returns 0, doesn't write into `s`.
 * `sz = 1` returns 0, writes '\0' into `s[0]`.
 * On read error, returns 0 and `s` will contain whatever's been read.
 */
size_t getline(char *s, size_t sz)
{
	int c;
	size_t i = 0;
	while (i + 1 < sz) {
		c = getchar();
		if (c == EOF) {
			if (!feof(stdin)) {
				s[i] = '\0';
				return 0;
			}
			break;
		}
		s[i++] = (char)c;
		if (c == '\n')
			break;
	}
	if (i + 1 <= sz)
		s[i] = '\0';
	return i;
}
