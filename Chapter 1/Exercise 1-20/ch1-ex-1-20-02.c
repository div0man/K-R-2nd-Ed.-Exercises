/* Exercise 1-20. Write a program `detab` that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed set
 * of tab stops, say every `n` columns. Should `n` be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>
#include <stdbool.h>

#define LINEBUF 10		// line buffer size
#define MAXTW	16		// max. tab stop width

size_t col = 0;			// current column

size_t getline(char line[], size_t sz);
void detab(char * restrict outs, char const * restrict ins, size_t tw);

int main()
{
	extern size_t col;					// current column

	char line[LINEBUF];					// input buffer
	size_t len;							// input buffer string length
	char xline[MAXTW*(LINEBUF-1) + 1];	// output buffer (expanded tabs)
	for (len = getline(line, LINEBUF); len > 0;
	len = getline(line, LINEBUF)) {
		detab(xline, line, 4);
		printf("%s", xline);
		if (line[len-1] == '\n')
			col = 0;
	}
	return 0;
}

/* detab: read a string from `ins`, replace all tabs with spaces and
 * write the result into `outs`. Assume '\0' terminated strings and that
 * `outs` is big enough. Relies on extern variable for column alignment.
 * tw - tab width
 */
void detab(char * restrict outs, char const * restrict ins, size_t tw)
{
	extern size_t col;	// current column
	size_t j = 0;
	for (size_t i = 0; ins[i] != '\0'; ++i) {
		if (ins[i] == '\t') {
			for (size_t tabdist = ((col + tw) / tw * tw) - col;
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
	while (i + 1 < sz && !el) {
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
		if (c == EOF && !feof(stdin)) { // EOF due to error
			i = 0;
		}
		s[i] = '\0';
	}
	return i;
}
