#include "vector.h"
#include <math.h>
#include <iostream.h>

vector::vector()
{
}

vector::~vector()
{
}

vector::vector(float x, float y, float z)
{
	coord[X] = x;
	coord[Y] = y;
	coord[Z] = z;
}

vector vector::operator+(const vector &v)
{
	return vector(coord[X] + v.coord[X], coord[Y] + v.coord[Y], coord[Z] + v.coord[Z]);
}

vector vector::operator-(const vector &v)
{
	return vector(coord[X] - v.coord[X], coord[Y] - v.coord[Y], coord[Z] - v.coord[Z]);
}

vector &vector::operator+=(const vector &v)
{
	coord[X] += v.coord[X];
	coord[Y] += v.coord[Y];
	coord[Z] += v.coord[Z];
	return *this;
}

vector &vector::operator-=(const vector &v)
{
	coord[X] -= v.coord[X];
	coord[Y] -= v.coord[Y];
	coord[Z] -= v.coord[Z];
	return *this;
}

float vector::operator*(const vector &v)
{
	return coord[X] * v.coord[X] + coord[Y] * v.coord[Y] + coord[Z] * v.coord[Z];
}

vector find_normal(vector &p0, vector &p1, vector &p2)
{
	vector v1, v2;
	v1 = p0 - p1;
	v2 = p2 - p1;
	return vector(v1.coord[Y] * v2.coord[Z] - v1.coord[Z] * v2.coord[Y], v1.coord[Z] * v2.coord[X] - v1.coord[X] * v2.coord[Z],
		v1.coord[X] * v2.coord[Y] - v1.coord[Y] * v2.coord[X]);
}

vector normalize(vector &v)
{
	float num = sqrt(v * v);

	return vector(v.coord[X] /= num, v.coord[Y] /= num, v.coord[Z] /= num);
}

void vector::show()
{
	cout << '(' << coord[X] << ',' << coord[Y] << ',' << coord[Z] << ')' << endl;
}

void vector::read()
{
	cin >> coord[X];
	cin >> coord[Y];
	cin >> coord[Z];
}
