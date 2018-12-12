/* Exercise 1-20. Write a program `detab` that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed set
 * of tab stops, say every `n` columns. Should `n` be a variable or a symbolic
 * parameter?
 */

#define LINEBUF 10 			// line buffer size
#include <stdio.h>
#include <stdbool.h>

size_t getline(char line[], size_t sz);
size_t detab(char s[], size_t tw, size_t startcol);

int main()
{
	size_t col = 0;
	char line[LINEBUF];
	size_t len;
	for (len = getline(line, LINEBUF); len > 0;
	len = getline(line, LINEBUF)) {
		col = detab(line, 4, col);
		if (line[len-1] == '\n')
			col = 0;
	}
	return 0;
}

/* detab: replace tabs inside s with blanks, returns end column;
 * tw - tab width
 * startcol - if a string is part of a big line, we don't count from 0
 */
size_t detab(char s[], size_t tw, size_t startcol)
{
	size_t tscol;		// nearest tab stop column
	size_t endcol;
	endcol = startcol;
	tscol = ((startcol + tw) / tw) * tw;
	for (size_t i = 0; s[i] != '\0'; ++i) {
		if (s[i] == '\t') {
			for (tscol -= endcol; tscol > 0; --tscol) {
					putchar(' ');
					++endcol;
			}
		}
		else {
			putchar(s[i]);
			++endcol;
		}
		tscol = ((endcol + tw) / tw) * tw;
	}
	return endcol;
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
