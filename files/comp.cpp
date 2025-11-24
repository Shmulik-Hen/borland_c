#include<string.h>
#include"c:\bc\prj\linklist.cpp"

class comp:public linklist{
	   public:
		   char *location;
		   char *description;
		   char *catno;
		   char *repl1;
		   char *repl2;
		   char *repl3;
	   public:
		   comp();
		   ~comp();
		   void read();
		   void print();
		   friend fstream& operator >> (fstream &fin, comp &c);
		   friend fstream& operator << (fstream &fout, comp &c);
		   friend char* strip(char *s);
	  };


comp::comp()
{
}

comp::~comp()
{
 delete location;
 delete description;
 delete catno;
 delete repl1;
 delete repl2;
 delete repl3;
 this->remove();
}

void comp::read()
{
}

void comp::print()
{
 cout<<location<<endl<<description<<endl
     <<catno<<endl<<repl1<<endl<<repl2<<endl<<repl3<<endl;
}

fstream& operator >> (fstream &fin, comp &c)
{
 char *str;
 int i=0;

 str=new char[256];

 do{
    fin.read(&str[i],1);
   }
 while( str[i++] != '\n');
 str[i-1]=NULL;

 c.location=strip(str);
 c.description=strip(NULL);
 c.catno=strip(NULL);
 c.repl1=strip(NULL);
 c.repl2=strip(NULL);
 c.repl3=strip(NULL);

 delete str;
 return (fin);
}

fstream& operator << (fstream &fout, comp &c)
{
 fout<<'\"'
 <<c.location<<"\",\""
 <<c.description<<"\",\""
 <<c.catno<<"\",\""
 <<c.repl1<<"\",\""
 <<c.repl2<<"\",\""
 <<c.repl3<<"\",\""
 <<"ELI\",\"1\""
 <<endl;
 return (fout);
}

char* strip(char *s)
{
 char *tmp,*p;

 tmp=strtok(s,",");
 p=tmp;
 while(*p)
      {
       if(*p=='\"')
	 strcpy(p,p+1);
       else
	   p++;
      }
 for(p=tmp;!(*p==' ');p++)
     strcpy(p,p+1);
 p=new char[1+strlen(tmp)];
 strcpy(p,tmp);
 return p;
}

linklist head;
comp *my;

void main()
{
 char file1[50]="c:\\catalog\\eli.da";
 char file2[50]="c:\\catalog\\xli.da";
 char *str;
 fstream f1,f2;
 comp *last;
 int found;

 //LOAD
 f1.open(file1,ios::in|ios::out|ios::nocreate);
 if(!f1)
    cout << "could not open file";
 last=(comp*)&head;
 while(!f1.eof())
   {
    my=new comp;
    f1 >> *my;
    my->append(last);
    last=my;
   }
 f1.close();
 delete last;

 /*
 //DELETE
 my=(comp*)&head;
 while(my->r_next() != NULL)
      {
       my=(comp*)&head;
       my=(comp*)my->r_next();
       delete my;
      }
 */

 //SAVE
 f2.open(file2,ios::out);
 if(!f2)
    cout << "could not open file";
 my=(comp*)&head;
 while(my->r_next() != NULL)
      {
       my=(comp*)my->r_next();
       f2 << *my;
      }
 f2.close();

 /*
 //SEARCH
 cout<<"enter location:";
 cin>>str;

 found=0;
 my=(comp*)&head;
 while(my->r_next() != NULL)
      {
       my=(comp*)my->r_next();
       if(!strcmp(my->location,str))
	 {
	  my->print();
	  found=1;
	 }
      }
 if(!found)
    cout << "no such component" << endl;

 //PRINT
 my=(comp*)&head;
 while(my->r_next() != NULL)
      {
       my=(comp*)my->r_next();
       my->print();
       getchar();
      }
 */
}