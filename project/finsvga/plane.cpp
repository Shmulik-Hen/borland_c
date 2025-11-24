#include "element.h"
#include "polyelem.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

extern list<polygon> poly_list;
extern matrix UNIT_MAT;
vector view(0,0,-1000000);
//vector n_light(-591,591,-591);
vector n_light(0,724,-724);
typedef char palette[3];
typedef void(*func)();
func func_table[256];
element *key_elem[50];
element *root=NULL;
int quit=0;

void init_palette();
void get_palette(palette buff[], int colors);
void set_palette(palette buff[], int colors);
int huge DetectVGA256();
void read_file();
void init();
void do_change();
void keep_moving();
void init_elements();
void init_funcs();
void roll_left();
void roll_right();
void pitch_up();
void pitch_down();
void turn_left();
void turn_right();
void gear_up_down();
void throt_up();
void throt_down();
void zoom();
void quit_game();
void no_op();

void main()
{
 polyelem *pe;
 init();

 key_elem[1]->update(attrib(0,0,0,0,0,0,768));
 //key_elem[10]->update(attrib(0,0,0,0,-75000,0,1024));
 key_elem[10]->active_flag=0;

 while(!quit)
   {
    while(!kbhit())
      {
       keep_moving();
       update_tree(root,UNIT_MAT,UNIT_MAT);
       pe=merge_sort();
       setfillstyle(1,203);
       bar(0,0,240,75);
       setfillstyle(1,150);
       bar(0,76,240,150);
       while(pe)
	 {
	  pe->show();
	  pe=pe->next;
	 }
       pe_free();
      }
    do_change();
   }
 closegraph();
}

void init_palette()
{
 int i,j;

 enum rgb{R,G,B};
 palette pal_16_colors[16];
 palette pal_256_colors[256];

 get_palette(pal_16_colors,16);
 for(i=0;i<16;i++)
   for(j=0;j<16;j++)
     {
      pal_256_colors[j*16+i][R]=(char)(((int)(pal_16_colors[i][R])*j)/15);
      pal_256_colors[j*16+i][G]=(char)(((int)(pal_16_colors[i][G])*j)/15);
      pal_256_colors[j*16+i][B]=(char)(((int)(pal_16_colors[i][B])*j)/15);
     }
 set_palette(pal_256_colors,256);
}

void get_palette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1017;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

void set_palette(palette buff[], int colors)
{
 struct REGPACK reg;

 reg.r_ax=0x1012;
 reg.r_bx=0;
 reg.r_cx=colors;
 reg.r_dx=FP_OFF(buff);
 reg.r_es=FP_SEG(buff);
 intr(0x10,&reg);
}

int huge DetectVGA256()
{
  return 0;/*
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n\n>");
  scanf("%d",&Vid);
  return Vid;*/
}

void read_file()
{
 char filename[]="plane.dat";
 ifstream f;
 LINE line;
 polygon *poly;
 element *elem1,*elem2;

 f.open(filename,ios::in|ios::nocreate);
 if(!f) error("file not found:",filename);
 f.unsetf(ios::skipws);
 while(!f.eof())
   {
    while( (!read_word(f,line)) && (!f.eof()) );
    switch(line[1])
      {
       case '#':read_remark(f);
       case 'p':poly=new polygon;
		poly->read(f);
		poly_list.insert(poly);
		break;
       case 'e':elem1=new element;
		elem1->read(f);
		if(!root)
		  root=elem1;
		else
		  {
		   elem2=root->find_elem(elem1->parrent);
		   if(elem2)
		      elem1->addnode(elem2);
		   else
		     error("element not found in tree::addnode()",elem1->parrent);
		  }
		break;
      }
   }
 f.close();
}

void init()
{
 read_file();
 int Gd = DETECT, Gm;
 installuserdriver("SVGA256",DetectVGA256);
 initgraph(&Gd,&Gm,"");
 init_palette();
 setviewport(40,25,280,175,1);
 init_funcs();
 init_elements();
}


void do_change()
{
 char c=getch();
 if(!c) c=getch();
 func_table[c]();
}

void keep_moving()
{
 key_elem[9]->update(attrib(0,0,64,0,0,0,1024));
 //key_elem[10]->update(attrib(0,0,0,0,0,-10240,1024));
}

void init_elements()
{
 key_elem[0]=root->find_elem("world");
 key_elem[1]=root->find_elem("plane");
 key_elem[2]=root->find_elem("rudder");
 key_elem[3]=root->find_elem("la_flap");
 key_elem[4]=root->find_elem("ra_flap");
 key_elem[5]=root->find_elem("lf_flap");
 key_elem[6]=root->find_elem("rf_flap");
 key_elem[7]=root->find_elem("l_gear");
 key_elem[8]=root->find_elem("r_gear");
 key_elem[9]=root->find_elem("prop");
 key_elem[10]=root->find_elem("ground");
 key_elem[11]=root->find_elem("square_11");
 key_elem[12]=root->find_elem("square_21");
 key_elem[13]=root->find_elem("square_31");
 key_elem[14]=root->find_elem("square_41");
 key_elem[15]=root->find_elem("square_12");
 key_elem[16]=root->find_elem("square_22");
 key_elem[17]=root->find_elem("square_32");
 key_elem[18]=root->find_elem("square_42");
 key_elem[19]=root->find_elem("square_13");
 key_elem[20]=root->find_elem("square_23");
 key_elem[21]=root->find_elem("square_33");
 key_elem[22]=root->find_elem("square_43");
 key_elem[23]=root->find_elem("square_14");
 key_elem[24]=root->find_elem("square_24");
 key_elem[25]=root->find_elem("square_34");
 key_elem[26]=root->find_elem("square_44");
 key_elem[27]=root->find_elem("gimble_1");
}

void init_funcs()
{
 for(int i=0;i<256;i++)
   func_table[i]=no_op;
 func_table[75]=roll_left;
 func_table[77]=roll_right;
 func_table[80]=pitch_up;
 func_table[72]=pitch_down;
 func_table[44]=turn_left;
 func_table[46]=turn_right;
 func_table[71]=gear_up_down;
 func_table[103]=gear_up_down;
 func_table[43]=throt_up;
 func_table[45]=throt_down;
 func_table[27]=quit_game;
 func_table[90]=zoom;
 func_table[122]=zoom;
}

void roll_left()
{
 //key_elem[1]->update(attrib(0,0,2,0,0,0,1024));
 key_elem[27]->update(attrib(0,0,4,0,0,0,1024));
 //key_elem[5]->update(attrib(8,0,0,0,0,0,1024));
 //key_elem[6]->update(attrib(-8,0,0,0,0,0,1024));
}

void roll_right()
{
 //key_elem[1]->update(attrib(0,0,-2,0,0,0,1024));
 key_elem[27]->update(attrib(0,0,-4,0,0,0,1024));
 //key_elem[5]->update(attrib(-8,0,0,0,0,0,1024));
 //key_elem[6]->update(attrib(8,0,0,0,0,0,1024));
}

void pitch_up()
{
 key_elem[1]->update(attrib(-4,0,0,0,0,0,1024));
 //key_elem[27]->update(attrib(-4,0,0,0,0,0,1024));
 //key_elem[3]->update(attrib(4,0,0,0,0,0,1024));
 //key_elem[4]->update(attrib(4,0,0,0,0,0,1024));
}

void pitch_down()
{
 key_elem[1]->update(attrib(4,0,0,0,0,0,1024));
 //key_elem[27]->update(attrib(4,0,0,0,0,0,1024));
 //key_elem[3]->update(attrib(-4,0,0,0,0,0,1024));
 //key_elem[4]->update(attrib(-4,0,0,0,0,0,1024));
}

void turn_left()
{
 key_elem[1]->update(attrib(0,4,0,0,0,0,1024));
 //key_elem[27]->update(attrib(0,4,0,0,0,0,1024));
}

void turn_right()
{
 key_elem[1]->update(attrib(0,-4,0,0,0,0,1024));
 //key_elem[27]->update(attrib(0,-4,0,0,0,0,1024));
}

void gear_up_down()
{
}

void throt_up()
{
}

void throt_down()
{
}

void zoom()
{
 static fact=0;
 switch(fact)
   {
    case 0:key_elem[1]->update(attrib(0,0,0,0,0,0,1365));
	   fact=1;
	   break;
    case 1:key_elem[1]->update(attrib(0,0,0,0,0,0,768));
	   fact=0;
	   break;
   }
}

void quit_game()
{
 quit=1;
}

void no_op()
{
}