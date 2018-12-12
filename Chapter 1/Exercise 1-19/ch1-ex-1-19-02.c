/* Exercise 1-19. Write a function `reverse(s)` that reverses the character
 * string `s`. Use it to write a program that reverses its input a line at a
 * time.
 */

/* Some improvements after comments received:
 * https://codereview.stackexchange.com/questions/206064/kr-exercise-1-19-reverse-program-input-one-line-at-a-time
 */

#include <stdio.h>
#include <stdbool.h>
#define BUFSIZE 10		// line buffer size

size_t getline(char line[], size_t maxsz);
void copy(char to[], char from[]);
void reverse(char s[]);
bool reverseinput(char lastchar[]);

int main(void)
{
	char lastchar;
	while (reverseinput(&lastchar) != 0) {
		if (lastchar == '\n') {
			putchar('\n');
		}
	}
	return 0;
}

/* reverseinput: read from input until end of line ('\n' or EOF) is
 * reached and then print the line in reverse, excluding the '\n';
 * keep track of the last character to detect EOF terminated line;
 * returns true if there's more of the input
 */
bool reverseinput(char* lastcharpt)
{
	size_t len;
	char line[BUFSIZE];
	bool retval;

	len = getline(line, BUFSIZE);
	if (len > 0) {
		*lastcharpt = line[len-1];
		if (line[len-1] == '\n') {
			// delete the '\n', we'll add it back to the end
			line[len-1] = '\0';
			retval = true;
		}
		else {
			retval = reverseinput(lastcharpt);
		}
		reverse(line);
		printf("%s", line);
	}
	else {
		retval = false;
	}
	return retval;
}

/* getline: read a line into `s`, return length;
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

/* reverse: reverse a '\0' terminated string
 */
void reverse(char s[])
{
	// find the end of character array
	size_t tail = 0;
	while (s[tail] != '\0') {
		++tail;
	}
	// move back to last character index
	if (tail > 0) {
		--tail;
	}
	// reverse the string by swapping first and last elements
	char c = 0;
	for (size_t head = 0; head < tail; ++head, --tail) {
		c = s[head];
		s[head] = s[tail];
		s[tail] = c;
	}
}
