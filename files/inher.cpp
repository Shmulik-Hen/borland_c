#include "list.cpp"
#include <iostream.h>
#include <string.h>

class details : public linklist
{
public:

	char *name;

private:

	char *address;
	int id;

public:

	details(const char *m_name, const char *m_address, int m_id);
	details();
	void print();
	void read();
};

class permanent : virtual public details
{
	int base_rate;
	int car_rate;
	int grade;

public:

	permanent(const char *m_name, const char *m_address, int m_id, int m_base_rate, int m_car_rate, int m_grade);
	permanent();
	void print(char pdtl);
	void read(char rdtl);
};

class temporary : virtual public details
{
	int hour_rate;
	int num_hours;

public:

		temporary(con{t char *m_name,const char *m_address,
			int m_id,int m_hour_rate,int m_num_hours);
		temporary();
		void print(char pdtl);
		void read(char rdtl);
};



class sales:virtual public permanent,
	    virtual public temporary
{
	public:

		sales(const char *m_name, const char *m_address, int m_id, int m_base_rate, int m_car_rate, int m_grade,
			int m_hour_rate, int m_num_hours);
		sales();
		void print();
		void read();
};

details::details(const char *m_name,const char *m_address,
			int m_id)
{
		name = new char[strlen(m_name) - 1];
		address = new char[strlen(m_address) - 1];
		strcpy(name, m_name);
		strcpy(address, m_address);
		id = m_id;
}

details::details()
{
}


void details::print()
{
		cout << name << endl;
		cout << address << endl;
}

void details::read()
{
		char m_name[20];
		char m_address[20];
		cout << "Enter name and address" << endl;
		cin >> m_name;
		cin >> m_address;
		name = new char[strlen(m_name) - 1];
		address = new char[strlen(m_address) - 1];
		strcpy(name, m_name);
		strcpy(address, m_address);
}


permanent::permanent(const char *m_name,const char *m_address,
			int m_id,int m_base_rate,int m_car_rate,int m_grade):
	details(m_name,m_address,m_id)
{
		base_rate = m_base_rate;
		car_rate = m_car_rate;
		grade = m_grade;
}

permanent::permanent():details()
{
}

void permanent::print(char pdtl)
{
		if (pdtl)
			details::print();
		cout << "base " << base_rate << endl;
		cout << "car  " << car_rate << endl;
		cout << "grade" << grade << endl;
		cout << "total" << base_rate + car_rate + grade << endl;
}

void permanent::read(char rdtl)
{
		if (rdtl)
			details::read();
		cout << "Enter base,car and grade" << endl;
		cin >> base_rate;
		cin >> car_rate;
		cin >> grade;
}


temporary::temporary(const char *m_name,const char *m_address,
			int m_id,int m_hour_rate,int m_num_hours):
	details(m_name,m_address,m_id)
{
		hour_rate = m_hour_rate;
		num_hours = m_num_hours;
}

temporary::temporary():details()
{
}

void temporary::print(char pdtl)
{
		if (pdtl)
			details::print();
		cout << "Hour rate " << hour_rate << endl;
		cout << "Number of hours" << num_hours << endl;
		cout << "Total " << hour_rate * num_hours << endl;
}

void temporary::read(char rdtl)
{
		if (rdtl)
			details::read();
		cout << "Enter hour rate and number of hours" << endl;
		cin >> hour_rate;
		cin >> num_hours;
}

sales::sales()
{
}

sales::sales(const char *m_name,const char *m_address,int m_id,
		      int m_base_rate,int m_car_rate,int m_grade,
		      int m_hour_rate,int m_num_hours):
	permanent(m_name,m_address,m_id,m_base_rate,m_car_rate,m_grade),
	temporary(m_name,m_address,m_id,m_hour_rate,m_num_hours)
{
}

void sales::print()
{
		temporary::print(1);
		permanent::print(0);
}

void sales::read()
{
		temporary::read(1);
		permanent::read(0);
}
