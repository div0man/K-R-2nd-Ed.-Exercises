/* Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much as
 * possible of the text.
 */

#include <stdio.h>
#include <stdbool.h>
#define BUFSIZE 10			// line buffer size

size_t getline(char line[], size_t sz);
void copy(char to[], char from[]);

/* print the longest input line length and the line itself or only the
 * part which could fit in the buffer 
 */
int main(void)
{
	size_t max = 0;			// length of longest line
	char longest[BUFSIZE];	// [beginning of] longest line

	size_t len;				// length of current line
	char line[BUFSIZE];		// [beginning of] current line
	len = getline(line, BUFSIZE);
	while (len > 0) {
		// If we didn't reach the end with getline, consume the input
		// until the end is reached while incrementing the length
		if (len == BUFSIZE-1 && line[BUFSIZE-2] != '\n') {
			int c;
			c = getchar();
			while (c != EOF && c != '\n') {
				++len;
				c = getchar();
			}
			if (c == '\n') {
				++len;
			}
		}
		if (len > max) {
				max = len;
				copy(longest, line);
		}
		len = getline(line, BUFSIZE);
	}

	if (max > 0) {
		// there was a line
		if (max > BUFSIZE-1) {
			printf("Longest line length: %ld, first ", max);
			printf("%d characters: \n%s\n", BUFSIZE-1, longest);
		}
		else {
			printf("Longest line length: %ld; longest line: \n%s\n",
			max, longest);
		}
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

/* copy: copy a '\0' terminated string `from` into `to`;
 * assume `to` is big enough;
 */
void copy(char to[], char from[])
{
	size_t i;
	for (i = 0; from[i] != '\0'; ++i) {
		to[i] = from[i];
	}
	to[i] = '\0';
}
