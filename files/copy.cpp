#include <fstream.h>

void main()
{
	int x = 0;
	char sin[20], sout[20], c;
	cout << "Enter source file name\n";
	cin >> sin;
	cout << "Enter dest. file name\n";
	cin >> sout;
	fstream fin(sin, ios::in | ios::binary | ios::nocreate), fout(sout, ios::out | ios::binary | ios::noreplace);
	while (!fin.eof()) {
		fin >> c;
		fout << c;
		x++;
	}
	cout << x;
}
