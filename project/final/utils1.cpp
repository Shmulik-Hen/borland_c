#include "polygon.h"
#include "element.h"
#include "utils.h"
#include "types.def"
#include "graphics.h"
#include <process.h>
#include <conio.h>

extern list<polygon> poly_list;
extern int quit;
extern element *root;

func func_table[256];
element *key_elem[50];
int wheel_break=1;
int wow=0;
int started=0;
int gear=0;
int of_flaps=0;
int oa_flaps=0;
int o_rudder=0;
long aoa=0;
long rpm=0;
long mph=0;
long d_mph=0;
long gear_angle=0;
long roll=0;
long pitch=0;
long yaw=0;
long alt=0;
long d_alt=0;
long heading=0;
long f_flaps=0;
long a_flaps=0;
long rudder=0;
typedef enum movement{l_roll,r_roll,u_pitch,d_pitch,l_turn,r_turn,none};
movement move=none;

void error(const char* s1, const char* s2)
{
 closegraph();
 cerr<<s1<<' '<<s2;
 exit(0);
}

int read_word(ifstream& f, char* word)
{
 word[0]='\0';
 int finish=0;
 int length=0;
 char c;

 while( (!finish) && (!f.eof()) && (length<MAX_LINE) )
   {
    f>>c;
    if( (c<=32)||(c==',')||(c=='(')||(c==')')||(c=='{')||(c=='}') )
      finish=1;
    else
      word[length++]=c;
   }
 word[length]='\0';
 return length;
}

void init()
{
 read_file();
 initgraph();
 setviewport(40,25,280,175);
 setcolor(255);
 bar(0,0,240,150);
 init_funcs();
 init_elements();
 key_elem[2]->update(attrib(-16,0,0,0,0,0,1000));
 key_elem[11]->update(attrib(0,0,0,0,-7000,0,1024));
}

void init_elements()
{
 key_elem[0]=root->find_elem("world");
 key_elem[1]=root->find_elem("gimble");
 key_elem[2]=root->find_elem("plane");
 key_elem[3]=root->find_elem("rudder");
 key_elem[4]=root->find_elem("la_flap");
 key_elem[5]=root->find_elem("ra_flap");
 key_elem[6]=root->find_elem("lf_flap");
 key_elem[7]=root->find_elem("rf_flap");
 key_elem[8]=root->find_elem("l_gear");
 key_elem[9]=root->find_elem("r_gear");
 key_elem[10]=root->find_elem("prop");
 key_elem[11]=root->find_elem("ground");
 key_elem[12]=root->find_elem("runway");
 key_elem[13]=root->find_elem("tower");
 key_elem[14]=root->find_elem("square_11");
 key_elem[15]=root->find_elem("square_21");
 key_elem[16]=root->find_elem("square_31");
 key_elem[17]=root->find_elem("square_41");
 key_elem[18]=root->find_elem("square_12");
 key_elem[19]=root->find_elem("square_22");
 key_elem[20]=root->find_elem("square_32");
 key_elem[21]=root->find_elem("square_42");
 key_elem[22]=root->find_elem("square_13");
 key_elem[23]=root->find_elem("square_23");
 key_elem[24]=root->find_elem("square_33");
 key_elem[25]=root->find_elem("square_43");
 key_elem[26]=root->find_elem("square_14");
 key_elem[27]=root->find_elem("square_24");
 key_elem[28]=root->find_elem("square_34");
 key_elem[29]=root->find_elem("square_44");

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
 func_table[71]=gear_active;
 func_table[103]=gear_active;
 func_table[43]=throt_up;
 func_table[45]=throt_down;
 func_table[27]=quit_game;
 func_table[90]=zoom;
 func_table[122]=zoom;
 func_table[83]=pause;
 func_table[115]=pause;
 func_table[13]=start;
 func_table[66]=breaks;
 func_table[98]=breaks;
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

void do_change()
{
 char c=getch();
 if(!c) c=getch();
 func_table[c]();
}

void keep_moving()
{
 key_elem[10]->update(attrib(0,0,rpm,0,0,0,1024)); //prop

 if(!wow) wheel_break=0;                           //gear
 if(!wheel_break)
   {
    mph+=d_mph;
    d_mph=0;
   }
 if(gear)
   {
    gear_up_down();
    key_elem[8]->update(attrib(0,0,-gear_angle,0,0,0,1024));
    key_elem[9]->update(attrib(0,0,gear_angle,0,0,0,1024));
   }

 key_elem[11]->update(attrib(0,0,0,0,0,mph,1024));

 if(alt<0)
   wow=0;
 if(!wow)
   {
    key_elem[1]->update(attrib(0,0,roll,0,0,0,1024));
    key_elem[2]->update(attrib(pitch,yaw,0,0,0,0,1024));
   }

 key_elem[3]->update(attrib(0,-rudder,0,0,0,0,1024));
 key_elem[4]->update(attrib(-a_flaps,0,0,0,0,0,1024));
 key_elem[5]->update(attrib(-a_flaps,0,0,0,0,0,1024));
 key_elem[6]->update(attrib(f_flaps,0,0,0,0,0,1024));
 key_elem[7]->update(attrib(-f_flaps,0,0,0,0,0,1024));
 f_flaps=0;
 a_flaps=0;
 rudder=0;
 d_alt=0;
}

void roll_left()
{
 if(move!=l_roll)
   {
    move=l_roll;
    reset_move();
    return;
   }
 if(roll<4)
   {
    roll+=1;
    heading-=4;
    f_flaps=16;
    of_flaps+=16;
   }
}

void roll_right()
{
 if(move!=r_roll)
   {
    move=r_roll;
    reset_move();
    return;
   }
 if(roll>-4)
   {
    roll-=1;
    heading+=4;
    f_flaps=-16;
    of_flaps-=16;
   }
}

void pitch_down()
{
 if(move!=d_pitch)
   {
    move=d_pitch;
    reset_move();
    return;
   }
 if(pitch<4)
   {
    pitch+=1;
    a_flaps=16;
    oa_flaps+=16;
   }
 aoa+=pitch;
}

void pitch_up()
{
 if(move!=u_pitch)
   {
    move=u_pitch;
    reset_move();
    return;
   }
 if(pitch>-4)
   {
    pitch-=1;
    a_flaps=-16;
    oa_flaps-=16;
   }
 aoa+=pitch;
}

void turn_left()
{
 if(move!=l_turn)
   {
    move=l_turn;
    reset_move();
    return;
   }
 if(yaw<4)
   {
    yaw+=1;
    rudder=16;
    o_rudder+=16;
   }
}

void turn_right()
{
 if(move!=r_turn)
   {
    move=r_turn;
    reset_move();
    return;
   }
 if(yaw>-4)
   {
    yaw-=1;
    rudder=-16;
    o_rudder-=16;
   }
}
void gear_active()
{
 gear=1;
}

void gear_up_down()
{
 static x=0;
 static long angle=128;

 if(wow) return;
 switch(x)
   {
    case 0:if(angle>0)
	     {
	      gear_angle=-4;
	      angle+=gear_angle;
	     }
	   else
	     {
	      key_elem[8]->active_flag=0;
	      key_elem[9]->active_flag=0;
	      x=1;
	      gear=0;
	      gear_angle=0;
	     }
	   break;
    case 1:key_elem[8]->active_flag=1;
	   key_elem[9]->active_flag=1;
	   if(angle<128)
	     {
	      gear_angle=4;
	      angle+=gear_angle;
	     }
	   else
	     {
	      x=0;
	      gear=0;
	      gear_angle=0;
	     }
	   break;
   }
}

void zoom()
{
 static fact=1;
 switch(fact)
   {
    case 0:key_elem[1]->update(attrib(0,0,0,0,0,0,2048));
	   fact=1;
	   break;
    case 1:key_elem[1]->update(attrib(0,0,0,0,0,0,512));
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

void pause()
{
 while(!kbhit());
}

void start()
{
 if(!rpm)
   {
    rpm=20;
    d_mph=-10240;
    started=1;
   }
}

void throt_up()
{
 if(!started) return;
 if(rpm<70)
   {
    rpm+=10;
    d_mph-=5120;
   }
}

void throt_down()
{
 if(!started) return;
 if(rpm>20)
   {
    rpm-=10;
    d_mph+=5120;
   }
}

void breaks()
{
 static x=1;
 switch(x)
   {
    case 0:wheel_break=1;
	   x=1;
	   if(rpm==20)
	     mph=d_mph=0;
	   break;
    case 1:wheel_break=0;
	   x=0;
	   if(rpm==20)
	     d_mph=-10240;
	   break;
   }
}

void reset_move()
{
 roll=0;
 pitch=0;
 yaw=0;
 f_flaps=-of_flaps;
 a_flaps=-oa_flaps;
 rudder=-o_rudder;
 of_flaps=0;
 oa_flaps=0;
 o_rudder=0;
}