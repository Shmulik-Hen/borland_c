#ifndef _DRAWING.H
#define _DRAWING.H

typedef struct vector
	{
	 int x;
	 int y;
	 vector *next_vector;
	}VECTOR;

typedef struct body
	{
	 int num_points;
	 int color;
	 vector *first_vector;
	}BODY;

void do_drawing();
void choose_color();
void put_image();
void transform(VECTOR *v);
#endif