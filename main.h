#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<stdargs.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE  1024
#define UNUSED(x) (void)(x)

/*FLAGS*/

#define F_MINUS 2
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/*SIZE*/

#define S_SHORT 1
#define S_LONG 2

/**
 * struct frmt - struct operator
 * 
 * @frmt: the format
 * @fn: function engaged
 */

struct frmt
{
	char frmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/*setting the above datatype to a shorter name using typedef*/
typedef struct frmt frmt_t;

int _printf(const char *format, ...);

int handle_print(const char *fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size);

/*FUNCTIONS*/

/*functions to print char and string*/

int print_char(va_list types, char buffer[], int flags, int width, int precision, int size);

int
