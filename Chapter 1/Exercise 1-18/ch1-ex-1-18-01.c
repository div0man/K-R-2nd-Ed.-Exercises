/* Exercise 1-18. Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 */

#include <stdio.h>
#include <stdbool.h>
#define BUFSIZE 10			// line buffer size

size_t getline(char line[], size_t sz);
void copy(char to[], char from[]);
size_t trimtrail(char line[]);

int main(void)
{
	size_t len;				// working length
	size_t nlen;			// peek length
	size_t tlen;			// trimmed length
	char line[BUFSIZE];		// working buffer
	char nline[BUFSIZE];	// peek buffer
	bool istail = false;
	bool ismore = false;

	len = getline(line, BUFSIZE);
	while (len > 0) {
		if (line[len-1] == '\n') {
			// proper termination can mean either a whole line, or end
			// of one
			tlen = trimtrail(line);
			if (istail == false) {
				// base case, whole line fits in the working buffer
				// print only non-empty lines
				if (line[0] != '\n') {
					printf("%s", line);
				}
			}
			else {
				// long line case, only the tail in the working buffer
				printf("%s", line);
				if (len != tlen) {
					// we couldn't keep the whole history so maybe more
					// blanks were seen which could not be processed;
					// run the program again to catch those
					ismore = true;
				}
			}
			// this always gets the [beginning of] next line
			len = getline(line, BUFSIZE);
			istail = 0;
		}
		else {
			// if it was not properly terminated, peek ahead to
			// determine whether there's more of the line or we reached
			// EOF
			nlen = getline(nline, BUFSIZE);
			if (nlen > 0) {
				if (nline[0]=='\n') {
					// if next read got us just the '\n'
					// we can safely trim the preceding buffer
					tlen = trimtrail(line);
					if (tlen > 0) {
						printf("%s", line);
						if (len != tlen)
							ismore = 1;
					}
				}
				else {
					// if still no '\n', we don't know if safe to trim
					// and can only print the preceding buffer here
					printf("%s", line);
				}
				// we didn't yet process the 2nd buffer so copy it into
				// 1st and run it through the loop above
				len = nlen;
				copy(line, nline);
				istail = 1;
			}
			else {
				// EOF reached, peek buffer empty
				// means we can safely trim the preceding buffer
				tlen = trimtrail(line);
				if (tlen > 0) {
					if (line[0]!='\n') {
						printf("%s", line);
					}
					else {
						ismore = 1;
					}
				}
				if (len != tlen) {
					ismore = 1;
				}
				// and we don't need to run the loop anymore, exit here
				len = 0;
			}
		}
	}
	// if there were too long lines, we could not trim them all;
	// signal to the environment that more runs could be required
	return ismore;
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

/* trimtrail: trim trailing tabs and blanks, returns new length
 */
size_t trimtrail(char s[])
{
	size_t lastnb;
	size_t i;
	// find the last non-blank char
	for (i = 0, lastnb = 0; s[i] != '\0'; ++i) {
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
			lastnb = i;
		}
	}
	// is it a non-empty string?
	if (i > 0) {
		--i;
		// is there a non-blank char?
		if (lastnb > 0 || 
		(s[0] != ' ' && s[0] != '\t' && s[0] != '\n')) {
			// has non-blanks, but is it properly terminated?
			if (s[i] == '\n') {
				++lastnb;
				s[lastnb] = '\n';
			}
		}
		else {
			// blanks-only line, but is it properly terminated?
			if (s[i] == '\n') {
				s[lastnb] = '\n';
			}
		}
		++lastnb;
		s[lastnb] = '\0';
		return lastnb;
	}
	else {
		// empty string
		return 0;
	}
}
