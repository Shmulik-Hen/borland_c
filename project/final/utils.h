#ifndef _UTILS_H
#define _UTILS_H
#include <fstream.h>
#include "types.def"

int read_word(ifstream &, char *);
void error(const char *s1, const char *s2 = "");
void init();
void init_elements();
void init_funcs();
void read_file();
void do_change();
void keep_moving();
void roll_left();
void roll_right();
void pitch_up();
void pitch_down();
void turn_left();
void turn_right();
void gear_active();
void gear_up_down();
void throt_up();
void throt_down();
void zoom();
void quit_game();
void no_op();
void pause();
void set_clocks();

#endif
