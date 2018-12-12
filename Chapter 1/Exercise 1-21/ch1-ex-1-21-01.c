/* Exercise 1-21. Write a program `entab` that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for `detab`. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */

#include <stdio.h>
#include <stdbool.h>

#define LINEBUF 2		// line buffer size
#define MAXTW	16		// max. tab stop width

size_t col = 0;			// current column

size_t getline(char line[], size_t sz);
void detab(char outs[], char ins[], size_t tw);
void entab(char s[], size_t tw);

int main()
{
	extern size_t col;					// current column
	col = 0;
	char line[LINEBUF];					// input buffer
	size_t len;							// input buffer string length
	for (len = getline(line, LINEBUF); len > 0;
	len = getline(line, LINEBUF)) {
		entab(line, 4);
		printf("%s", line);
		if (line[len-1] == '\n')
			col = 0;
	}
	return 0;
}

void entab(char s[], size_t tw)
{
	extern size_t col;	// current column
	size_t tcol = col;	// target column
	size_t j = 0;
	bool gotnul = false;
	for (size_t i = 0; !gotnul; ++i) {
		// on blank or tab just continue reading and move our target
		// column forward
		if (s[i] == ' ') {
			++tcol;
		}
		else if (s[i] == '\t') {
			tcol = (tcol+tw)/tw*tw;
		}
		else {
			// on non-blank char, if we're lagging behind target fill-up
			// with tabs & spaces and then write the char, else just
			// write the char
			if (tcol > col) {
				for (size_t at = (tcol/tw*tw-col/tw*tw)/tw; at > 0;
				--at) {
					s[j] = '\t';
					++j;
					col = (col+tw)/tw*tw;
				}
				for (size_t as = tcol-col; as > 0; --as) {
					s[j] = ' ';
					++j;
					++col;
				}
			}
			s[j] = s[i];
			if (s[i] == '\0') {
				gotnul = true;
			}
			else {
				++j;
				++col;
				++tcol;
			}
		}
	}
}

/* detab: read a string from `ins`, replace all tabs with spaces and
 * write the result into `outs`. Assume '\0' terminated strings and that
 * `outs` is big enough. For alignment, tracks current column via extern
 * variable.
 * tw - tab width
 */
void detab(char outs[], char ins[], size_t tw)
{
	extern size_t col;	// current column
	size_t j = 0;
	for (size_t i = 0, tabdist; ins[i] != '\0'; ++i) {
		if (ins[i] == '\t') {
			for (tabdist = ((col + tw) / tw * tw) - col;
			tabdist > 0; --tabdist) {
					outs[j] = ' ';
					++j;
					++col;
			}
		}
		else {
			outs[j] = ins[i];
			++j;
			++col;
		}
	}
	outs[j] = '\0';
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
