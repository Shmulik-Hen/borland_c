#ifndef _UNIT_H
#define _UNIT_H
#include <fstream.h>
extern long SIN[];
extern long *COS;
class unit
      {
	long num;
       public:
	unit(){};
	~unit(){};
	unit(const long& n){num=n;};
	unit operator+(const unit& u) const {return unit(num+u.num);};
	unit operator-(const unit& u) const {return unit(num-u.num);};
	unit operator*(const unit& u) const {return unit(((num>>1)*(u.num>>1))>>8);};
	unit operator/(const unit& u) const {return unit((num<<10)/u.num);};
	unit operator-() const {return unit(num * -1);};
	unit& operator+=(const unit& u) {num+=u.num;return *this;};
	unit& operator-=(const unit& u) {num-=u.num;return *this;};
	unit& operator*=(const unit& u) {num=((num>>1)*(u.num>>1))>>8;return *this;};
	unit& operator/=(const unit& u) {num=(num<<10)/u.num;return *this;};
	operator int() {return (int)(num>>10);};
	operator long() {return num;};
	friend int operator>(const unit& n1,const unit& n2) {return(n1.num > n2.num);};
	friend int operator>=(const unit& n1,const unit& n2) {return(n1.num >= n2.num);};
	friend int operator<(const unit& n1,const unit& n2) {return(n1.num < n2.num);};
	friend long convert(const char*);
	friend int mod(const long& n) {return int(n & 0x01ff);};
	friend unit abs(const unit& u) {return unit(u.num>0?u.num:u.num* -1);};
	friend unit sin(const unit& u) {return unit(SIN[mod(u.num)]);};
	friend unit cos(const unit& u) {return unit(COS[mod(u.num)]);};
	void read(ifstream&);
      };

const unit UNIT(1024);
const unit ZERO(0);
#endif
