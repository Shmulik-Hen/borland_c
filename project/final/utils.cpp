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
int scale[20] = {0, 15, 9, 12, 14, 5, 14, -5, 9, -12, 0, -15, -9, -12, -14, -5, -14, 5, -9, 12};
char *temp;

int wow = 1;
int gear = 0;

long roll = 0;
long pitch = 0;
long yaw = 0;
long alt = 0;
long aoa = 0;
long vvi = 0;
long adi = 0;
long heading = 0;
long gear_angle = 0;
long rpm = 0;
long mph = 0;
long f_flaps = 0;
long tf_flaps = 0;
long a_flaps = 0;
long ta_flaps = 0;
long rudder = 0;
long t_rudder = 0;
int rpm_idx = 0;
int mph_idx = 0;
int hdg_idx = 0;
int aoa_idx = 0;
int alt_idx = 0;
int adi_idx = 0;

void error(const char *s1, const char *s2)
{
	closegraph();
	cerr << s1 << ' ' << s2;
	exit(0);
}

int read_word(ifstream &f, char *word)
{
	word[0] = '\0';
	int finish = 0;
	int length = 0;
	char c;

	while ((!finish) && (!f.eof()) && (length < MAX_LINE)) {
		f >> c;
		if ((c <= 32) || (c == ',') || (c == '(') || (c == ')') || (c == '{') || (c == '}'))
			finish = 1;
		else
			word[length++] = c;
	}
	word[length] = '\0';
	return length;
}

void init()
{
	read_file();
	initgraph();
	put_scr();
	temp = new char[9600];
	if (!temp)
		error("not enough memory in init().");
	getimage(40, 160, 280, 198, temp);
	setcolor(250);
	bar(296, 171, 305, 179);
	setviewport(40, 2, 281, 152);
	init_funcs();
	init_elements();
	// key_elem[1]->update(attrib(0,64,0,0,0,0,1024));
	key_elem[2]->update(attrib(-16, 0, 0, 0, 0, 0, 1000));
	key_elem[11]->update(attrib(0, 0, 0, 0, -7000, 0, 1024));
}

void init_elements()
{
	key_elem[0] = root->find_elem("world");
	key_elem[1] = root->find_elem("gimble");
	key_elem[2] = root->find_elem("plane");
	key_elem[3] = root->find_elem("rudder");
	key_elem[4] = root->find_elem("la_flap");
	key_elem[5] = root->find_elem("ra_flap");
	key_elem[6] = root->find_elem("lf_flap");
	key_elem[7] = root->find_elem("rf_flap");
	key_elem[8] = root->find_elem("l_gear");
	key_elem[9] = root->find_elem("r_gear");
	key_elem[10] = root->find_elem("prop");
	key_elem[11] = root->find_elem("ground");
	key_elem[12] = root->find_elem("runway");
	key_elem[13] = root->find_elem("tower");
	/*
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
	*/
}

void init_funcs()
{
	for (int i = 0; i < 256; i++)
		func_table[i] = no_op;
	func_table[75] = roll_left;
	func_table[77] = roll_right;
	func_table[80] = pitch_up;
	func_table[72] = pitch_down;
	func_table[44] = turn_left;
	func_table[46] = turn_right;
	func_table[71] = gear_active;
	func_table[103] = gear_active;
	func_table[43] = throt_up;
	func_table[45] = throt_down;
	func_table[27] = quit_game;
	func_table[90] = zoom;
	func_table[122] = zoom;
	func_table[83] = pause;
	func_table[115] = pause;
}

void read_file()
{
	char filename[] = "plane.dat";
	ifstream f;
	LINE line;
	polygon *poly;
	element *elem1, *elem2;

	f.open(filename, ios::in | ios::nocreate);
	if (!f)
		error("file not found:", filename);
	f.unsetf(ios::skipws);
	while (!f.eof()) {
		while ((!read_word(f, line)) && (!f.eof()))
			;
		switch (line[1]) {
		case 'p':
			poly = new polygon;
			poly->read(f);
			poly_list.insert(poly);
			break;
		case 'e':
			elem1 = new element;
			elem1->read(f);
			if (!root)
				root = elem1;
			else {
				elem2 = root->find_elem(elem1->parrent);
				if (elem2)
					elem1->addnode(elem2);
				else
					error("element not found in tree::addnode()", elem1->parrent);
			}
			break;
		}
	}
	f.close();
}

void do_change()
{
	char c = getch();
	if (!c)
		c = getch();
	func_table[c]();
}

void keep_moving()
{
	unit Z_LIMIT(-50000);
	key_elem[10]->update(attrib(0, 0, rpm, 0, 0, 0, 1024)); // prop

	if (gear) {
		gear_up_down();
		key_elem[8]->update(attrib(0, 0, -gear_angle, 0, 0, 0, 1024));
		key_elem[9]->update(attrib(0, 0, gear_angle, 0, 0, 0, 1024));
	}

	key_elem[11]->update(attrib(0, 0, 0, 0, 0, mph, 1024));
	alt += vvi;
	// if(alt<0 && alt>-100000)
	if (alt < 0)
		key_elem[11]->update(attrib(0, 0, 0, heading, vvi, 0, 1024));
	if (key_elem[11]->att.off_y < Z_LIMIT) {
		key_elem[12]->active_flag = 0;
		key_elem[13]->active_flag = 0;
	}
	set_clocks();
}

void roll_left()
{
	if (tf_flaps <= 0) {
		f_flaps = 48;
		tf_flaps += 48;
		key_elem[6]->update(attrib(f_flaps, 0, 0, 0, 0, 0, 1024));
		key_elem[7]->update(attrib(-f_flaps, 0, 0, 0, 0, 0, 1024));
		heading += 3000;
	}
	if (wow)
		return;
	adi += 4;
	key_elem[1]->update(attrib(0, 0, 4, 0, 0, 0, 1024));
}

void roll_right()
{
	if (tf_flaps >= 0) {
		f_flaps = -48;
		tf_flaps -= 48;
		key_elem[6]->update(attrib(f_flaps, 0, 0, 0, 0, 0, 1024));
		key_elem[7]->update(attrib(-f_flaps, 0, 0, 0, 0, 0, 1024));
		heading -= 3000;
	}
	if (wow)
		return;
	adi -= 4;
	key_elem[1]->update(attrib(0, 0, -4, 0, 0, 0, 1024));
}

void pitch_up()
{
	if (ta_flaps <= 0) {
		a_flaps = 48;
		ta_flaps += 48;
		key_elem[4]->update(attrib(a_flaps, 0, 0, 0, 0, 0, 1024));
		key_elem[5]->update(attrib(a_flaps, 0, 0, 0, 0, 0, 1024));
	}
	if (wow)
		return;
	if (vvi > -4000)
		vvi -= 1000;
	if (aoa > -64) {
		aoa -= 16;
		pitch = -16;
		key_elem[2]->update(attrib(pitch, 0, 0, 0, 0, 0, 1024));
	}
}

void pitch_down()
{
	if (ta_flaps >= 0) {
		a_flaps = -48;
		ta_flaps -= 48;
		key_elem[4]->update(attrib(a_flaps, 0, 0, 0, 0, 0, 1024));
		key_elem[5]->update(attrib(a_flaps, 0, 0, 0, 0, 0, 1024));
	}
	if (wow)
		return;
	if (vvi < 4000)
		vvi += 1000;
	if (aoa < 64) {
		aoa += 16;
		pitch = 16;
		key_elem[2]->update(attrib(pitch, 0, 0, 0, 0, 0, 1024));
	}
}

void turn_left()
{
	if (t_rudder >= 0) {
		rudder = -64;
		t_rudder -= 64;
		key_elem[3]->update(attrib(0, rudder, 0, 0, 0, 0, 1024));
	}
	if (wow)
		return;
	key_elem[2]->update(attrib(0, 4, 0, 0, 0, 0, 1024));
}

void turn_right()
{
	if (t_rudder <= 0) {
		rudder = 64;
		t_rudder += 64;
		key_elem[3]->update(attrib(0, rudder, 0, 0, 0, 0, 1024));
	}
	if (wow)
		return;
	key_elem[2]->update(attrib(0, -4, 0, 0, 0, 0, 1024));
}

void gear_active()
{
	gear = 1;
}

void gear_up_down()
{
	static x = 0;
	static long angle = 128;

	if (wow)
		return;
	switch (x) {
	case 0:
		if (angle > 0) {
			gear_angle = -4;
			angle += gear_angle;
		}
		else {
			key_elem[8]->active_flag = 0;
			key_elem[9]->active_flag = 0;
			x = 1;
			gear = 0;
			gear_angle = 0;
			setviewport(0, 0, 319, 199);
			setcolor(1);
			bar(296, 171, 305, 179);
			setviewport(40, 2, 281, 152);
		}
		break;
	case 1:
		key_elem[8]->active_flag = 1;
		key_elem[9]->active_flag = 1;
		if (angle < 128) {
			gear_angle = 4;
			angle += gear_angle;
		}
		else {
			x = 0;
			gear = 0;
			gear_angle = 0;
			setviewport(0, 0, 319, 199);
			setcolor(250);
			bar(296, 171, 305, 179);
			setviewport(40, 2, 281, 152);
		}
		break;
	}
}

void zoom()
{
	static fact = 1;
	switch (fact) {
	case 0:
		key_elem[2]->update(attrib(0, 0, 0, 0, 0, 0, 2048));
		fact = 1;
		break;
	case 1:
		key_elem[2]->update(attrib(0, 0, 0, 0, 0, 0, 512));
		fact = 0;
		break;
	}
}

void quit_game()
{
	quit = 1;
}

void no_op()
{
}

void pause()
{
	while (!kbhit())
		;
}

void throt_up()
{
	if (rpm < 70) {
		rpm += 10;
		mph -= 5120;
		rpm_idx += 2;
		mph_idx += 2;
		if (wow && mph < -10240)
			key_elem[2]->update(attrib(4, 0, 0, 0, 0, 0, 1024));
		if (wow && mph == -35840) {
			wow = 0;
			pitch_up();
		}
	}
}

void throt_down()
{
	if (rpm > 10) {
		rpm -= 10;
		mph += 5210;
		rpm_idx -= 2;
		mph_idx -= 2;
	}
}

void set_clocks()
{
	setviewport(0, 0, 319, 199);

	putimage(40, 160, 280, 198, temp);

	setcolor(255);
	line(260, 180, 260 + scale[rpm_idx], 180 + scale[rpm_idx + 1]);
	line(220, 180, 220 + scale[mph_idx], 180 + scale[mph_idx + 1]);

	setviewport(40, 2, 281, 152);
}
