#include "utils.h"
#include <fstream.h>

void main()
{
 char filename[]="fs.dat";
 char filename2[]="fs.out";
 ifstream f;
 ofstream f2;
 LINE line;
 f.open(filename,ios::in|ios::nocreate);
 f.unsetf(ios::skipws);
 f2.open(filename2,ios::in|ios::nocreate);
 if(!f) error("file not found:",filename);
 while(!f.eof())
   {
    while(!read_word(f,line));
    f2<<line<<endl;
   }
 f.close();
 f2.close();
}
