#ifndef _VECTOR_H
#define _VECTOR_H

enum coords
{
	X,
	Y,
	Z
};
class vector
{
public:

	float coord[3];
	vector();
	~vector();
	vector(float x, float y, float z);
	vector operator+(const vector &v);
	vector operator-(const vector &v);
	vector &operator+=(const vector &v);
	vector &operator-=(const vector &v);
	float operator*(const vector &v);
	friend vector find_normal(vector &p0, vector &p1, vector &p2);
	friend vector normalize(vector &);
	void show();
	void read();
};
#endif
