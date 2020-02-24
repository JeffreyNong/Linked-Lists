//
//  main.c
//  rpn
//
//  Created by William McCarthy on 192//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP   100    /* max size of operand/operator */
#define NUMBER '0'     /* signal that a number was found */
#define MAXVAL  100

size_t sp = 0;   // aka unsigned long -- printf using %zu
double val[MAXVAL];   // stack of values

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch: too many characters\n");  return; }
  buf[bufp++] = c;
}

int getop(char* s) {
  int i, c;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }  // skip whitespace
  s[1] = '\0';

  if (!isdigit(c) && c != '.') { return c; }  // if not a digit, return

  i = 0;
  if (isdigit(c)) {  // get digits before '.'
    while (isdigit(s[++i] = c = getch_())) { }
  }
  if (c == '.') {    // get digits after decimal (if any)
    while (isdigit(s[++i] = c = getch_())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;      // return type is NUMBER, number stored in s
}

double pop(void) {
  if (sp == 0) { fprintf(stderr, "stack underflow\n");  return 0.0; }
  return val[--sp];
}

void push(double f) {
  if (sp == MAXVAL) { fprintf(stderr, "stack overflow -- can't push %g\n", f);  return; }
  val[sp++] = f;
}
double head(void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void duplicate(void)
{
    push(head());
}

void swap(void)
{
    double swap;
    int i;

    if (sp < 2)
        printf("error: can not swap, not enough elements\n");
    else {
        i = sp - 1;
        swap = val[i - 1];
        val[i - 1] = val[i];
        val[i] = swap;
    }
}

void clear(void)
{
    while (--sp >= 0)
        val[sp] = 0.0;
    sp = 0;
}
void rpn(void) {
  int type, var = 0;
  double op2,v;
  char s[BUFSIZ];
  double variable[26];

  while ((type = getop(s)) != EOF) {
    switch(type) {
      case '\n':    printf("\t%.8g\n", pop());  break;
      case NUMBER:  push(atof(s));              break;
      case '+':     push(pop() + pop());        break;
      case '*':     push(pop() * pop());        break;
      case '-':     push(-(pop() - pop()));     break;
      case '%'://4.3
        if ((op2 = pop()) == 0.0 ){ fprintf(stderr, "divide by zero\n");  break; }
        push((int) pop % (int) op2);
        break;
        case '?':
            printf("top of the stack: %f\n", head());
            break;
        case '$':
            printf("duplicate top of the stack\n");
            duplicate();
            break;
        case '!':
            printf("swap the top two elements of stack\n");
            swap();
            break;
        case '#':
            printf("clear stack\n");
            clear();
            break;
      case '/':
        if ((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n");  break; }
        push(pop() / op2);
        break;
      default:
      if(type >= 'A' && type <='Z')//4.6
        push(variable[type-'A']);
        else if(type == 'v')
        push(v);
        else
        fprintf(stderr, "unknown command %s\n", s);  break;
    }
    var = type;
  }
}

int main(int argc, const char * argv[]) {
  rpn();

  return 0;
}
