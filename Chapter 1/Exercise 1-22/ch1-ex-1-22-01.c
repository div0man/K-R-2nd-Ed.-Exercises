/* Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXTW	8		// max. tab width
#define MAXFC	10	// max. fold column
#define LINEBUF	MAXFC+200	// line buffer size, must be >MAXFC+1

size_t getline(char line[], size_t sz);
void copy(char * restrict to, char const * restrict from);
size_t foldline(char * restrict ins, char * restrict outs, size_t fcol,
 size_t tw);
size_t fillbuf(char s[], size_t sz);

int main(void)
{
	char line[LINEBUF];					// input buffer
	size_t len;							// input buffer string length

	size_t	fcol = 10;					// column to fold at
	size_t	tw = 4;						// tab width

	if (fcol > MAXFC) {
		return -1;
	}

	if (tw > MAXTW) {
		return -2;
	}

	len = getline(line, LINEBUF);
	while (len > 0) {
		char xline[LINEBUF];	// folded part
		size_t xlen;			// folded part string length

		xlen = foldline(line, xline, fcol, tw);
		printf("%s", line);

		if (xlen > 0) {
			copy(line, xline);
			if (line[xlen-1] != '\n') {
				len = fillbuf(line, LINEBUF);
			}
			else {
				len = xlen;
			}
		}
		else {
			len = getline(line, LINEBUF);
		}
	}
	return 0;
}

// assumes buffer starts after a newline
size_t foldline(char * restrict ins, char * restrict outs, size_t fcol,
 size_t tw)
{
	size_t col;
	size_t i;
	size_t lnbi;
	char lc = ' ';
	for (col = 0, i = 0, lnbi = 0; ins[i] != '\0' && ins[i] != '\n' && col < fcol;
	 ++i) {
		if (ins[i] == ' ') {
			++col;
			if (lc != ' ' && lc != '\t') {
				lnbi = i-1;
			}
		}
		else if (ins[i] == '\t') {
			col = (col + tw) / tw * tw;
			if (lc != ' ' && lc != '\t') {
				lnbi = i-1;
			}
		}
		else {
			++col;
		}
		lc = ins[i];
	}
	// i & col are now either at the position of termination (\0 or \n) or the 
	// char preceding the overflow column. lnbi is at last non-blank we can fold at

	if (col < fcol) {
		// no folding, terminated before the break column
		outs[0] = '\0';
		// return 0 after the if block
	}
	else if (col == fcol && (ins[i+1] == '\n' || ins[i+1] == '\0')) {
		// no folding, termination in the break column
		outs[0] = '\0';
		// return 0 after the if block
	}
	else if ((lnbi > 0) || ((ins[0] != ' ' && ins[0] != '\t'))) {
		// folding at last non-whitespace char
		size_t j, k;
		for (j = 0, k = ++lnbi; ins[k] != '\0'; ++j, ++k) {
			outs[j] = ins[k];
		}
		outs[j] = '\0';
		ins[lnbi++] = '\n';
		ins[lnbi] = '\0';
		return j;
	}
	else {
		// whitespace-only line; fold at overflow
		size_t j, k;
		for (j = 0, k = i+1; (ins[k] != '\0' && ins[k] != '\n'); ++j, ++k) {
			outs[j] = ins[k];
		}
		if (ins[k] == '\n') {
			outs[j++] = '\n';
			outs[j] = '\0';
		}
		else {
			outs[j] = '\0';
		}
		ins[i++] = '\n';
		ins[i] = '\0';
		return j;
	}
	return 0;
}

// user must ensure that the buffer has free space for at least 1 char
// returns total string length
size_t fillbuf(char s[], size_t sz)
{
	// find end of string
	size_t i;
	for (i = 0; s[i] != '\0'; ++i) {
	}

	return i + getline(&s[i], sz-i);
	// the above not introduced in the book; for "hardcore" version, we
	// could simply c&p `getline` code here
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
