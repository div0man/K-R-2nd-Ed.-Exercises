/* **Exercise 4-5.** Add access to library functions like `sin`, `exp`, and
 * `pow`. See `<math.h>` in Appendix B, Section 4.
 */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <math.h>

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0'		/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);

/* reverse Polish calculator */
int main(void)
{
	int type;
	double op1;
	double op2;
	char s[MAXOP];

	type = getop(s);
	while (type != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0) {
				op1 = pop();
				push(op1 - (int)(op1 / op2) * op2);
			}
			else {
				printf("error: zero divisor\n");
			}
			break;
		case 'p':
			op2 = pop();
			push(op2);
			printf("\t%.8g\n", op2);
			break;
		case 'd':
			op2 = pop();
			push(op2);
			push(op2);
			break;
		case 's':
			op2 = pop();
			op1 = pop();
			push(op2);
			push(op1);
			break;
		case 'a':
			clear();
			break;
		case 'l':
			type = getop(s);
			if (type == EOF)
				break;
			switch (type) {
				case 's':
					push(sin(pop()));
					break;
				case 'c':
					push(cos(pop()));
					break;
				case 'e':
					push(exp(pop()));
					break;
				case 'p':
					op2 = pop();
					push(pow(pop(), op2));
					break;
				default:
					printf("error: unknown command l%s\n", s);
					break;
			}
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
		type = getop(s);
	}
	return 0;
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* clear: clear the stack */
void clear(void)
{
	sp = 0;
	val[0] = 0.0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = (char)(c = getch())) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if (c == '-') {
		if ((isdigit(c = getch()) || c == '.')) {
			s[1] = (char)c;
			s[2] = '\0';
			i = 1;
		}
		else {
			ungetch(c);
			c = s[0];
		}
	}
	if (!isdigit(c) && c != '.')
		return c;		/* not a number */
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = (char)(c = getch())))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = (char)(c = getch())))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE	100

char buf[BUFSIZE];		/* buffer for ungetch */
int bufp = 0;			/* next free position in buf */

int getch(void)		/* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)		/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = (char)c;
}
