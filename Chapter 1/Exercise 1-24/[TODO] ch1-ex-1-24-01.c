/* Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments. (This program
 * is hard if you do it in full generality.)
 */

#include <stdio.h>
#include <stdbool.h>

int line = 0;
int parentheses = 0;
int brackets = 0;
int braces = 0;

void do_base(int c);
int run_base (int c);
void do_macro(int c);
int run_macro(int c);
void do_quote(int c);
int run_quote(int c);
void do_comment(int c);
int run_comment(int c);

int main(void)
{
	int c = getchar();
	while (c != EOF)
		c = run_base(c);
	return 0;
}

/* Process all "base" characters in the input.
 * The routine calls separate routines to process non-base segments it runs
 * into.
 */
int run_base (int c)
{
	while (c != EOF) {
		// process potential macro statement
		// it can only start at the beginning of line (ignoring whitespace)
		if (c == '\n') {
			do_base(c);
			c = getchar();
			while (c == ' ' || c == '\t') {
				do_base(c);
				c = getchar();
			}
			if (c == '#') {
				c = run_macro(c);
			}
		}
		// process quote statement
		else if (c == '\'' || c == '\"') {
			c = run_quote(c);
		}
		// process potential comment statement
		else if (c == '/') {
			int p = c;
			c = getchar();
			if (c == '/' || c == '*') {
				do_comment(p);
				c = run_comment(c);
			}
			else {
				do_base(p);
			}
		}
		// continue processing "base"
		else {
			do_base(c);
			c = getchar();
		}
	}
	return c;
}

void do_base (int c)
{
	extern int line;
	extern int parentheses;
	extern int brackets;
	extern int braces;
	if (c == '\n') {
		++line;
	}
	else if (c == '(') {
		parentheses
}

/* Process all characters in the macro directive.
 */
int run_macro(int c)
{
	do_macro('#');
	c = getchar();
	while (c == ' ' || c == '\t') {
		do_macro(c);
		c = getchar();
	}
	while (c != EOF && c != ' ' && c != '\t' && c != '\n') {
		if (c == '\\') {
			do_macro('\\');
			c = getchar();
			// any '\n' preceded by the escape char is processed as inside macro
			if (c == '\n') {
				do_macro('\n');
				c = getchar();
			}
		}
		else {
			do_macro(c);
			c = getchar();
		}
	}
	if (c != EOF) {
		do_macro(c);
		c = getchar();
	}
	return c;
}

void do_macro(int c)
{
	extern int line;
	if (c == '\n')
		++line;
}

/* Process all characters in the quote statement.
 */
int run_quote(int c)
{
	int q = c;
	do_quote(c);
	c = getchar();
	while (c != EOF && c != '\n') {
		// any char preceded by the escape char is processed as inside quote
		if (c == '\\') {
			do_quote('\\');
			c = getchar();
			if (c != EOF) {
				do_quote(c);
				c = getchar();
			}
		}
		else if (c == q) {
			do_quote(c);
			c = getchar();
			break;
		}
		else {
			do_quote(c);
			c = getchar();
		}
	}
	return c;
}

void do_quote(int c)
{
	extern int line;
	if (c == '\n')
		++line;
}

/* Process all characters in the comment statement.
 */
int run_comment(int c)
{
	int q = c;
	do_comment(c);
	c = getchar();
	if (q == '*') {
		while (c != EOF) {
			// potential termination
			if (c == '*') {
				do_comment('*');
				c = getchar();
				if (c == '/') {
					do_comment(c);
					c = getchar();
					break;
				}
			}
			else {
				do_comment(c);
				c = getchar();
			}
		}
	}
	else { // if (q == '/')
		while (c != EOF && c != '\n') {
			// any \n preceded by the escape char is processed as inside comment
			if (c == '\\') {
				do_comment('\\');
				c = getchar();
				if (c == '\n') {
					do_comment('\n');
					c = getchar();
				}
			}
			else {
				do_comment(c);
				c = getchar();
			}
		}
	}
	return c;
} 

void do_comment(int c)
{
	extern int line;
	if (c == '\n')
		++line;
}
