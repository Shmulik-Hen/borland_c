/****************************************************************************
*                                                                           *
* SUBJECT:	Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        Graphic Instruction File Utility.  (header)                 *
* ------                                                                    *
*                                                                           *
* FILE:		intrprt2.h                                                  *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:	Iron Ran	023914260	"iron"                      *
* -----------	Sholkis Moshe   059764993	"shool"                     *
*                                                                           *
****************************************************************************/


ELEMENT *find_element(ELEMENT *list,NAME *name);
POLYGON *find_polygon(POLYGON *list,NAME *name);
ELEMENT *search_element(LINE path);
ELEMENT *get_parent(LINE path,NAME name);


int read_element(FILE *f);
int read_polygon(FILE *f);
int read_film(FILE *f);
int read_file(FILE *f);
int read_screen(FILE *f);
int run_film();
int init_traps();

int screen_viewport	();
int screen_textxy	();
int screen_box		();
int screen_back		();
int screen_clear	();
int screen_line		();
int screen_pause	();
int screen_sky		();
int screen_ground	();

int load_int	   (FILM *temp_film,FILE *f);
int load_e_path	   (FILM *temp_film,FILE *f);

int load_label	   (FILM *temp_film,FILE *f);
int load_event     (FILM *temp_film,FILE *f);
int load_attrib    (FILM *temp_film,FILE *f);
int load_var	   (FILM *temp_film,FILE *f);
int load_jump	   (FILM *temp_film,FILE *f);
int load_trap      (FILM *temp_film,FILE *f);
int load_untrap    (FILM *temp_film,FILE *f);
int load_vector    (FILM *temp_film,FILE *f);
int load_show      (FILM *temp_film,FILE *f);
int load_viewport  (FILM *temp_film,FILE *f);
int load_element   (FILM *temp_film,FILE *f);

int load_macrodump (FILM *temp_film,FILE *f);
int load_macroload (FILM *temp_film,FILE *f);

int load_branch	   (FILM *temp_film,FILE *f);
int load_beq	   (FILM *temp_film,FILE *f);
int load_bneq	   (FILM *temp_film,FILE *f);
int load_bbig	   (FILM *temp_film,FILE *f);
int load_bless	   (FILM *temp_film,FILE *f);
int load_cp_var	   (FILM *temp_film,FILE *f);

int load_cp_atof   (FILM *temp_film,FILE *f);
int load_cp_atof   (FILM *temp_film,FILE *f);
int load_cp_atof   (FILM *temp_film,FILE *f);
int load_cp_atoi   (FILM *temp_film,FILE *f);
int load_cp_atoi   (FILM *temp_film,FILE *f);
int load_cp_atoi   (FILM *temp_film,FILE *f);
int load_cp_atof   (FILM *temp_film,FILE *f);
int load_var_name  (FILM *temp_film,FILE *f);
int load_op	   (FILM *temp_film,FILE *f);
int load_add_var   (FILM *temp_film,FILE *f);
int load_cycle_xz  (FILM *temp_film,FILE *f);



int do_end	  ();
int do_delay	  ();
int do_label	  ();
int do_branch	  ();
int do_event	  ();
int do_showall	  ();
int do_attrib	  ();

int do_var	  ();
int do_add	  ();
int do_load	  ();
int do_jzero	  ();
int do_jnzero	  ();

int do_trap	  ();
int do_untrap	  ();
int do_dotrap	  ();
int do_viewmove	  ();
int do_lightmove  ();
int do_setview	  ();
int do_setlight   ();
int do_show	  ();
int do_viewport   ();
int do_flippage   ();
int do_hide	  ();
int do_expose     ();
int do_macrorun   ();
int do_macrostop  ();
int do_macrodump  ();
int do_macroload  ();
int do_cp_var	  ();
int do_cp_ctr_x	  ();
int do_cp_ctr_y	  ();
int do_cp_ctr_z	  ();
int do_cp_off_x	  ();
int do_cp_off_y	  ();
int do_cp_off_z	  ();
int do_cp_deg_x	  ();
int do_cp_deg_y	  ();
int do_cp_deg_z	  ();
int do_cp_zoom	  ();
int do_cp_view_x  ();
int do_cp_view_y  ();
int do_cp_view_z  ();
int do_cp_light_x ();
int do_cp_light_y ();
int do_cp_light_z ();
int do_branch	  ();
int do_beq	  ();
int do_bneq	  ();
int do_bbig	  ();
int do_bless	  ();
int do_op_init	  ();
int do_op_off_x   ();
int do_op_off_y	  ();
int do_op_off_z	  ();
int do_op_deg_x	  ();
int do_op_deg_y	  ();
int do_op_deg_z	  ();
int do_op_zoom	  ();
int do_op	  ();
int do_sky	  ();
int do_ground	  ();
int do_add_var    ();
int do_back	  ();
int do_cycle_xz   ();
