#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char      uint8_t; 
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;


typedef signed char       sint8_t;
typedef signed short int  sint16_t;
typedef signed int        sint32_t;
typedef signed long long  sint64_t;

typedef float             float32_t;
typedef double            float64_t;
typedef long double       float86_t;


typedef struct node* stack_t;


typedef struct grade
{
	float32_t cs;
	float32_t math;
	float32_t english;

}grade_t;


typedef struct date
{
	uint8_t day;
	uint8_t month;
	uint16_t year;

}date_t;


typedef struct Student
{
	uint64_t phone_number;
	uint8_t  address [50];
	uint8_t  name    [30];
	uint32_t ID;
	date_t date;
	grade_t grade;

}student_t;



#endif