/* Exercise 1-21. Write a program `entab` that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for `detab`. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXTW	4		// max. tab stop width
#define LINEBUF MAXTW	// line buffer size, must be >=MAXTW

size_t col = 0;			// current column
size_t tcol = 0;		// target column

size_t getline(char line[], size_t sz);
void copy(char * restrict to, char const * restrict from);
size_t entab(char s[], size_t tw);

int main(void)
{
	extern size_t col;					// current column
	extern size_t tcol;					// target column

	char line[LINEBUF];					// input buffer
	size_t len;							// input buffer string length
	
	size_t tw = 4;						// tab width

	if (tw > MAXTW) {
		return -1;
	}

	len = getline(line, LINEBUF);
	while (len > 0) {
		len = entab(line, tw);
		if (line[len-1] == '\n') {
			// base case, working with a full, properly terminated line
			// or a tail of one; we can safely print it
			col = 0;
			tcol = 0;
			printf("%s", line);
			len = getline(line, LINEBUF);
		}
		else if (line[len-1] != ' ') {
			// could be part of a bigger line or end of stream and we
			// don't have dangling blanks; we can safely print it
			printf("%s", line);
			len = getline(line, LINEBUF);
		}
		else {
			// we have some dangling blanks and must peek ahead to
			// know whether we can merge them into a tab or not
			bool cantab = false;
			char pline[LINEBUF];	// peek buffer
			size_t plen;			// peek buffer string length
			plen = getline(pline, LINEBUF);
			if (plen > 0) {
				if (pline[0] == ' ') {
					// count spaces in the peek; pspc = 1 because if
					// we're here then we already know pline[0] == ' '
					size_t pspc;
					for (pspc = 1; (pline[pspc] == ' ' ||
					pline[pspc] == '\t') && pspc < plen &&
					pspc < tw; ++pspc) {
						if (pline[pspc] == '\t') {
							cantab = true;
						}
					}
					// enough to warrant a tab stop?
					if (col + pspc >= (col + tw)/tw*tw) {
						cantab = true;
					}
				}
				else if (pline[0] == '\t') {
					cantab = true;
				}
			} // else we got EOF and those spaces have to stay
			if (cantab) {
				// pop the spaces and adjust current column accordingly
				while (len > 0 && line[--len] == ' ') {
					--col;
					line[len] = '\0';
				} // no need to fix len, as it gets reset below
			}
			printf("%s", line);
			len = plen;
			copy(line, pline);
		}
	}
	return 0;
}

/* entab: process string from `s`, replace in-place spaces with tabs.
 * Assume '\0' terminated string. Relies on extern variable for column
 * alignment.
 * tw - tab width
 */
size_t entab(char s[], size_t tw)
{
	extern size_t col;	// current column
	extern size_t tcol;	// target column
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
			if (s[j] == '\0') {
				gotnul = true;
			}
			else {
				++j;
				++col;
				++tcol;
			}
		}
	}
	return j;
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
	while (i + 1 < sz && !el) {
		c = getchar();
		if (c == EOF) {
			el = true; // note: `break` not introduced yet
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
		if (c == EOF && !feof(stdin)) { // EOF due to read error
			i = 0;
		}
		s[i] = '\0';
	}
	return i;
}

/* copy: copy a '\0' terminated string `from` into `to`;
 * assume `to` is big enough;
 */
void copy(char * restrict to, char const * restrict from)
{
	size_t i;
	for (i = 0; from[i] != '\0'; ++i) {
		to[i] = from[i];
	}
	to[i] = '\0';
}
