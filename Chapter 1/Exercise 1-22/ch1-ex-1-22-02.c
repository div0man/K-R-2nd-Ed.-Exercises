/* Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXTW	16			// max. tab width
#define MAXFC	100			// max. fold column, must be >=MAXTW
#define LINEBUF	MAXFC+2		// line buffer size, must be >MAXFC+1

size_t getline(char line[], size_t sz);
void copy(char * restrict to, char const * restrict from);
size_t foldline(char * restrict ins, char * restrict outs, size_t fcol,
 size_t tw); // style Q, how to indent this best?
size_t fillbuf(char s[], size_t sz);

int main(void)
{
	char line[LINEBUF];		// input buffer
	size_t len;				// input buffer string length

	size_t	fcol = 10;		// column to fold at
	size_t	tw = 4;			// tab width

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

		// fold the line (or part of one)
		xlen = foldline(line, xline, fcol, tw);
		printf("%s", line);

		// did we fold?
		if (xlen > 0) {
			// we printed only the first part, and must run the 2nd part through
			// the loop as well
			copy(line, xline);
			if (line[xlen-1] == '\n') {
				len = xlen;
			}
			else {
				// if there's no '\n' at the end, there's more of the line and
				// we must fill the buffer to be able to process it properly
				len = fillbuf(line, LINEBUF);
			}
		}
		else {
			len = getline(line, LINEBUF);
		}
	}
	return 0;
}

/* Folds a line at the given column. The input string gets truncated to have
 * `fcol` chars + '\n', and the excess goes into output string.
 * Non-destructive (doesn't delete whitespace) and adds a '\' char before the
 * '\n' if it has to break a word. Can be reversed by deleting
 * "(?<=\ )\n|(?<=\t)\n|\\\n" regex pattern matches unless the original file had
 * matches as well.
 */
size_t foldline(char * restrict ins, char * restrict outs, size_t fcol,
 size_t tw)
{
	/* Find i & col such that they will mark either the position of termination
	 * (\0 or \n) or whatever the char in the overflow column.
	 * Find lnbi such that it will mark the last non-blank char before the
	 * folding column.
	 */
	size_t i;
	size_t lnbi;
	size_t col;
	char lc = ' ';
	for (col = 0, i = 0, lnbi = 0; ins[i] != '\0' && ins[i] != '\n' &&
	 col < fcol; ++i) {
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

	// Determine where to fold at
	size_t foldat;
	if (col < fcol) {
		// don't fold, terminated before the fold column
		outs[0] = '\0';
		return 0;
	}
	else if (col == fcol) {
		// maybe fold, we have something in the overflow
		if (ins[i] == '\n' || ins[i] == '\0') {
			// don't fold, termination can stay in the overflow
			outs[0] = '\0';
			return 0;
		}
		else if (lnbi > 0 || (ins[0] != ' ' && ins[0] != '\t' && (ins[1] == ' '
		 || ins[1] == '\t'))) {
			// fold after the whitespace following the last non-blank char
			foldat = lnbi+2;
		}
		else {
			// fold at overflow
			foldat = i;
		}
	}
	else {
		// col > fcol only possible if ins[i-1] == '\t' so we fold and place the
		// tab on the next line
		foldat = i-1;
	}

	// Fold
	size_t j = 0, k;
	// add a marker if we're folding after a non-blank char
	if (ins[foldat-1] != ' ' && ins[foldat-1] != '\t') {
		outs[j++] = ins[foldat-1];
		ins[foldat-1] = '\\';
	}
	for (k = foldat; ins[k] != '\0'; ++j, ++k) {
		outs[j] = ins[k];
	}
	outs[j] = '\0';
	ins[foldat++] = '\n';
	ins[foldat] = '\0';
	return j;
}

/* continue reading a line into `s`, return total string length;
 * the buffer must have free space for at least 1 more char
 */
size_t fillbuf(char s[], size_t sz)
{
	// find end of string
	size_t i;
	for (i = 0; s[i] != '\0'; ++i) {
	}

	// not introduced in the book, but we could achieve the same by c&p
	// getline code here
	return i + getline(&s[i], sz-i);
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
