#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

namespace pclc {
	#define BUFSIZE 100
	#define MAXOP 100
	#define NUMBER '0'
	#define MAXVAL 100
	#define ERROR -1
	#define OK 0
	# define M_PIl 3.141592653589793238462643383279502884L /* pi */

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
		}
		return ERROR;
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
		if (!isdigit(c) && c != '.' && c != 'e') {
			return c;
		}
		if (isdigit(c)) {
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
		if (c == '.') {
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
		if (c == 'e') {
			while (isdigit(s[++i] = c = getch()) || c == '-') {
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
		double power;
		char s[MAXOP];
		//size_t bufflen = getline(s, MAXOP);
		
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
				case 'P':
					power = pop();
					push(pow(pop(), power));
					break;
				case 'E':
					push(exp(pop()));
					break;
				case 'S':
					push(pop()*M_PIl/180);
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

	double pick() {
		if (sp > 0) {
			return val[sp];
		}
		return ERROR;
	}

	int swapTop() {
		if (sp > 1) {
			double top_2 = val[sp - 1];
			val[sp - 1] = val[sp];
			val[sp] = top_2;
			return OK;
			//std::swap(val[sp], val[sp - 1]);
		}
		return ERROR;
	}

	int copyTop() {
		if (sp >= 1) {
			val[sp + 1] = val[sp];
			sp++;
			return OK;
		}
		return ERROR;
	}

	void clear() {
		memset(val, 0, sizeof(MAXVAL));
		memset(_buffer, 0, sizeof(BUFSIZE));
		sp = 0;
		_buff_pos = 0;
		sign = 0;
	}

	void ungets(char s[]) {
		for (size_t ptr = 0; s[ptr] != '\0'; ptr++) {
			ungetch(s[ptr]);
		}
	}
}	//pclc