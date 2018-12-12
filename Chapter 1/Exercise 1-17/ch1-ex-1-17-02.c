/* Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 */

#include <stdio.h>
#include <stdbool.h>
#define MINLENGTH	50	// min. line length for printout
#define BUFSIZE		51	// buffer size, must be greater than MINLENGTH

size_t getline(char line[], size_t sz);

/* print all input lines which are longer than MINLENGTH
 */
int main(void)
{
	size_t len;				// length of [beginning of] current line
	char line[BUFSIZE];		// [beginning of] current line
	len = getline(line, BUFSIZE);
	while (len > 0) {
		if (len >= MINLENGTH) {
			printf("%s", line);
			/* If we didn't reach the end with getline,
			 * continue printing until the end is reached */
			if (len == BUFSIZE-1 && line[BUFSIZE-2] != '\n') {
				int c;
				c = getchar();
				while (c != EOF && c != '\n') {
					putchar(c);
					c = getchar();
				}
				if (c == '\n') {
					putchar('\n');
				}
			}
		}
		len = getline(line, BUFSIZE);
	}
	return 0;
}

/* getline: read a line into `s`, return string length;
 * `sz` must be >1 to accomodate at least one character and string
 * termination '\0'
 */
size_t getline(char s[], size_t sz)
{
	int c;
	size_t i = 0;
	bool el = false;
	while (i < sz-1 && el == false) {
		c = getchar();
		if (c == EOF) {
			el = true;
		}
		else {
			s[i] = (char) c;
			++i;
			if (c == '\n') {
				el = true;
			}
		}
	}
	if (i < sz) {
		s[i] = '\0';
	}
	return i;
}
