#include "attrib.h"

attrib::attrib(unit dx, unit dy, unit dz, unit ox, unit oy, unit oz, unit z)
{
	deg_x = dx;
	deg_y = dy;
	deg_z = dz;
	off_x = ox;
	off_y = oy;
	off_z = oz;
	zoom = z;
}

attrib &attrib::operator+=(const attrib &a)
{
	deg_x += a.deg_x;
	deg_y += a.deg_y;
	deg_z += a.deg_z;
	off_x += a.off_x;
	off_y += a.off_y;
	off_z += a.off_z;
	zoom *= a.zoom;
	return *this;
}

void attrib::read(ifstream &f)
{
	deg_x.read(f);
	deg_y.read(f);
	deg_z.read(f);
	off_x.read(f);
	off_y.read(f);
	off_z.read(f);
	zoom.read(f);
}
