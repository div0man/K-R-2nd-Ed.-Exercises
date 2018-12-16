/* **Exercise 3-2.** Write a function `escape(s,t)` that converts characters
 * like newline and tab into visible escape sequences like `\n` and `\t` as it
 * copies the string `t` to `s`. Use a `switch`. Write a function for the other
 * direction as well, converting escape sequences into the real characters.
 */

#include <stdio.h>

#define BUFSIZE 1024

void escape(char * restrict s, char const * restrict t);
void unescape(char * restrict s, char const * restrict t);
size_t getline(char *s, size_t sz);

int main(void)
{
	char str[BUFSIZE];
	char esc[BUFSIZE * 2];
	size_t len;
	while ((len = getline(str, BUFSIZE)) > 0) {
		printf("Original=<%s>\n", str);
		escape(esc, str);
		for (size_t i = 0; i < BUFSIZE; ++i)
			str[i] = '\0';
		printf("Escaped=<%s>\n", esc);
		unescape(str, esc);
		printf("Unescaped=<%s>\n", str);
	}
}

/* escape: copy a '\0' terminated string `from` into `to` while replacing
 * characters like '\n' and '\t' into visible escape sequences.
 * Assume `to` is big enough.
 */
void escape(char * restrict to, char const * restrict from)
{
	size_t j = 0;
	for (size_t i = 0; from[i] != '\0'; ++i, ++j) {
		switch (from[i]) {
		case '\n':
			to[j++] = '\\';
			to[j] = 'n';
			break;
		case '\t':
			to[j++] = '\\';
			to[j] = 't';
			break;
		case '\\':
			to[j++] = '\\';
			to[j] = '\\';
			break;
		default:
			to[j] = from[i];
			break;
		}
	}
	to[j] = '\0';
}

/* unescape: copy a '\0' terminated string `from` into `to` while replacing
 * escape sequences with real characters.
 * Assume `to` is big enough.
 */
void unescape(char * restrict to, char const * restrict from)
{
	size_t j = 0;
	for (size_t i = 0; from[i] != '\0'; ++i, ++j) {
		if (from[i] == '\\') {
			switch (from[++i]) {
			case 'n':
				to[j] = '\n';
				break;
			case 't':
				to[j] = '\t';
				break;
			case '\\':
				to[j] = '\\';
				break;
			case '\0':
				break;
			default:
				to[j] = from[i];
				break;
			}
		}
		else {
			to[j] = from[i];
		}
	}
	to[j] = '\0';
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
