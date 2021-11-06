#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

namespace pclc {
	#define BUFSIZE 100
	#define MAXOP 100
	#define NUMBER '0'
	#define MAXVAL 100
	#define ERROR -1
	#define OK 0

	int sign = 0;
	int sp = 0;
	int _buff_pos = 0;
	double val[MAXVAL];
	char _buffer[BUFSIZE];

	int getline(char s[], int lim = MAXOP) {
		int c, i;
		i = 0;
		while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
			s[i++] = c;
		}
		if (c == '\n') {
			s[i++] = '\n';
		}
		s[i] = '\0';
		return i;
	}

	void push(double num) {
		if (sp < MAXVAL) {
			val[sp++] = num;
		} else {
			printf("push: too many double in stack\n");
		}
	}

	double pop(void) {
		if (sp > 0) {
			return val[--sp];
		} else {
			return ERROR;
		}
		return 0.0;
	}

	int getch(void) {
		return (_buff_pos > 0) ? _buffer[--_buff_pos] : getchar();
    }

	void ungetch(int num) {
		if (_buff_pos >= BUFSIZE) {
			printf("ungetch: too many char in buffer\n");
		} else {
			_buffer[_buff_pos++] = num;
		}
	}

	int getop(char s[]) {
		int i;
		int c;
		int ctr = 0;
		while ((s[0] = c = getch()) == ' ' || c == '\t') {
			;
		}
		s[1] = '\0';
		i = 0;
		if (c == '-') {
			while (isdigit(s[++i] = c = getch())) {
				ctr++;
			}
			if (ctr > 0) {
				s[i] = '\0';
				if (c != EOF) {
					ungetch(c);
				}
				return NUMBER;
			}
			return '-';
		}
		if (!isdigit(c) && c != '.') {
			return c;
		}
		if (isdigit(c)) {
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
		s[i] = '\0';
		if (c != EOF) {
			ungetch(c);
		}
		return NUMBER;
	}

	int calcMainLoop(void) {

		int type;
		double op;
		char s[MAXOP];

		while ((type = getop(s)) != EOF) {
			switch (type) {
				case NUMBER:
					push(atof(s));
					break;
				case '+':
					push(pop() + pop());
					break;
				case '-':
					op = pop();
					push(pop() - op);
					break;
				case '/':
					op = pop();
					if (op != 0.0) {
						push(pop() / op);
					} else {
						printf("ERROR: div by zero\n");
						return ERROR;
					}
					break;
				case '*':
					push(pop() * pop());
					break;
				case '%':
					op = pop();
					if (op != 0.0) {
						push((int)pop() % (int)op);
					} else {
						printf("ERROR: div by zero\n");
						return ERROR;
					}
					break;
				case '\0':
				case 'EOF':
				case '\n':
					printf("%f", pop());
					return OK;
					break;
				default:
					printf("ERROR: unknown calculator cmd - %s\n", s);
					return ERROR;
					break;
			}
		}
		return OK;
	}
}	//pclc