#include "attrib.h"

void attrib::read(ifstream& f)
{
 deg_x.read(f);
 deg_y.read(f);
 deg_z.read(f);
 off_x.read(f);
 off_y.read(f);
 off_z.read(f);
 zoom.read(f);
}