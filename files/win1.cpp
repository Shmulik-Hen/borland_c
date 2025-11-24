#include <win.h>

win::win()
{
}

win::~win()
{
 delete []buffer;
 delete []temp;
}
		    
win::win(int wid, int len, int fcol, int bcol,int border)
{
 unsigned char c;
 int row,col;

 width=wid;
 length=len;
 fcolor=fcol;
 bcolor=bcol;
 buf_size=width*length;

 b=buffer=new unsigned int[buf_size];
 temp=new unsigned int[buf_size];

 for(row=0;row<length;row++)
    {
     for(col=0;col<width;col++)
	{
	 if(border)
	   {
	    c=0x20;
	    if(row==0 || row==length-1)
	       c=0xcd;
	    if(col==0 || col==width-1)
	       c=0xba;
	    if(row==0 && col==0)
	       c=0xc9;
	    if(row==0 && col==width-1)
	       c=0xbb;
	    if(row==length-1 && col==0)
	       c=0xc8;
	    if(row==length-1 && col==width-1)
	       c=0xbc;
	   }
	 else
	    c=0x20;
	 *b++=(((bcolor<<4)+fcolor)<<8)+c;
	}
    }
}

void win::save()
{
 int row,col;
 b=buffer;
 s=screen;

 for(row=0;row<length;row++)
    {
     for(col=0;col<width;col++)
	{
	 *b++=*s++;
	}
     s+=(80-width);
    }
}

void win::show(int col, int row)
{
 s=(unsigned int far*)0xb8000000L;
 int x,y;

 t=temp;
 b=buffer;
 screen=s+=(80*(row-1) + col-1);

 for(y=row;y<(row+length);y++)
    {
     for(x=col;x<(col+width);x++)
	{
	 *t++=*s++;
	}
     s+=(80-width);
    }

 t=temp;
 s=screen;

 for(y=row;y<(row+length);y++)
    {
     for(x=col;x<(col+width);x++)
	{
	 *s++=*b++;
	}
     s+=(80-width);
    }
}

void win::hide()
{
 int row,col;
 s=screen;
 t=temp;

 for(row=0;row<length;row++)
    {
     for(col=0;col<width;col++)
	{
	 *s++=*t++;
	}
     s+=(80-width);
    }
}

void win::put_ch(char c, int col, int row, int fcol)
{
 if( col<=(width-1) && row<=length )
   {
    s=screen;
    s+=(80*row + col);
    *s=(((bcolor<<4)+fcol)<<8)+c;
   }
}

void win::put_str(char *str, int col, int row, int fcol)
{
 char c;
 while((c=*str++) != NULL)
      {
       if(col>=(width-1))
	 {
	  row++;
	  col-=(width-2);
	 }
       put_ch(c,col++,row,fcol);
      }
}

void win::get_str(char s[], int col, int row, int len, int fcol)
{
 char c,*p;

 p=s;
 while(len)
  {
   c=getch();
   if(c>='0' && c<='9')
     {
      *p++=c;
      put_ch(c,col++,row,fcol);
      len--;
     }
  }
 *p='\0';
}

void win::chg_attr(int col, int row, int len, int fcol, int bcol)
{
 s=screen;

 s+=(80*row + col);
 while(len--)
      {
       *s=(*s & 0x00ff) + (((bcol<<4)+fcol)<<8);
       s++;
      }
}

void win::fill(int start_row, int end_row, char c, int fcol, int bcol)
{
 int row,col;
 s=screen;

 s+=80*(start_row-1);
 for(row=start_row;row<=end_row;row++)
    {
     for(col=0;col<width;col++)
	{
	 *s++=(((bcol<<4)+fcol)<<8)+c;
	}
     s+=(80-width);
    }
}

int win::find_next(int col, int row)
{
 s=screen;
 s+=(80*row + col);
 while(isupper(*s++))
       col++;
 while(!isupper(*s++))
       col++;
 return ++col;
}

int win::find_prev(int col, int row)
{
 s=screen;
 s+=(80*row + --col);
 while(!isupper(*s--))
       col--;
 while(isupper(*s--))
       col--;
 return col;
}
