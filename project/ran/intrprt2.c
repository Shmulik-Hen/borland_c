/****************************************************************************
*                                                                           *
* SUBJECT:      Computer Graphics .                                         *
* --------                                                                  *
*                                                                           *
* TITLE:        Graphic Instruction File Utility.                           *
* ------                                                                    *
*                                                                           *
* FILE:         intrprt2.c                                                  *
* -----                                                                     *
*                                                                           *
* WRITTEN BY:   Iron Ran        023914260       "iron"                      *
* -----------   Sholkis Moshe   059764993       "shool"                     *
*                                                                           *
* UPDATES:      First Writing   18/11/94                                    *
* --------      Modify #1       27/12/94        Update To EX-2              *
*               Modify #2       29/12/94        "Traps" insted "Event"      *
*               Modify #3       22/01/95        Screen Commands             *
*               Modify #4       15/03/95        Final.                      *
*                                                                           *
*****************************************************************************
*                                                                           *
* DESCRIPTION:                                                              *
* ------------                                                              *
* this file containes the "load time" functions to load the film file into  *
* the memory , create all data structures & interperet all the film         *
* commands.                                                                 *
* for "run time" there are prucedures to operate on the graphic tree        *
* according to the film data.                                               *
*                                                                           *
****************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

#include "types.def"
#include "intrprt2.h"
#include "int_math.h"
#include "util.h"
#include "3d_util.h"

extern  MATRIX IDENT_MATRIX;
#define ORIGEN  {0,0,0}

/******************
* local variables *
******************/

/******************************
* film load & run varibles    *
******************************/

int     sky_color=0;                            // sky background color
int     ground_color=0;                         // ground background color
VECTOR  view=ORIGEN;                            // view point vector
VECTOR  n_view=ORIGEN;                          // normal view point
VECTOR  light=ORIGEN;                           // light source
VECTOR  n_light=ORIGEN;                         // normal light source


static  FILM *s_start_command=NULL;             // first film command
static  FILM *s_current_command=NULL;           // current film command
static  ELEMENT *s_main_element=NULL;           // main drawing element
static  POLYGON *s_first_polygon=NULL;          // first polygon pointer
static  POLY_ELEM *s_first_polyelem=NULL;       // first poly-elem pointer
static  POLY_ELEM *s_draw_polyelem=NULL;        // first poly-elem to draw

static  char s_key;                             // temp key
static  int s_macro_on=OFF;                     // macro active flag
static  int s_event_time=0;                     // event time counter
static  int s_last_mac_key=0;                   // last macro key index
static  LINE s_line;                            // temp line
static  int  s_finish=OFF;                      // film finish flag
static  long s_diff=0;                          // temp diffrance
static  ATTRIB s_operator;                      // temp attribute operator

static char far s_CODE[65535];                  // get segment for film
static unsigned s_last_code=0;                  // pointer in film segment

#define s_COMMAND_PREFIX        '#'
#define s_PATH_SEPARATOR        "\\/."



/*****************************
* load & run time procedures *
*****************************/

static struct
	{
	 NAME name;
	 int (*load_time)();
	 int (*run_time)();
	}
	s_film_commands[]=
			// command name ,load procedure ,run procedure

		     {  {"DELAY"        ,load_int       ,do_delay       },
			{"END"          ,NULL           ,do_end         },

			{"LABEL"        ,load_label     ,do_label       },
			{"EVENT"        ,load_event     ,do_event       },
			{"SHOWALL"      ,NULL           ,do_showall     },
			{"ATTRIB"       ,load_attrib    ,do_attrib      },
			{"CYCLE_XZ"     ,load_cycle_xz  ,do_cycle_xz    },

			{"VAR"          ,load_var       ,do_var         },
			{"ADD"          ,load_cp_var    ,do_add         },
			{"ADD_VAR"      ,load_add_var   ,do_add_var     },
			{"LOAD"         ,load_cp_var    ,do_load        },
			{"JZERO"        ,load_jump      ,do_jzero       },
			{"JNZERO"       ,load_jump      ,do_jnzero      },

			{"CP_VAR"       ,load_cp_var    ,do_cp_var      },
			{"CP_CTR_X"     ,load_cp_atof   ,do_cp_ctr_x    },
			{"CP_CTR_Y"     ,load_cp_atof   ,do_cp_ctr_y    },
			{"CP_CTR_Z"     ,load_cp_atof   ,do_cp_ctr_z    },
			{"CP_OFF_X"     ,load_cp_atof   ,do_cp_off_x    },
			{"CP_OFF_Y"     ,load_cp_atof   ,do_cp_off_y    },
			{"CP_OFF_Z"     ,load_cp_atof   ,do_cp_off_z    },
			{"CP_DEG_X"     ,load_cp_atoi   ,do_cp_deg_x    },
			{"CP_DEG_Y"     ,load_cp_atoi   ,do_cp_deg_y    },
			{"CP_DEG_Z"     ,load_cp_atoi   ,do_cp_deg_z    },
			{"CP_ZOOM"      ,load_cp_atof   ,do_cp_zoom     },

			{"CP_VIEW_X"    ,load_int       ,do_cp_view_x   },
			{"CP_VIEW_Y"    ,load_int       ,do_cp_view_y   },
			{"CP_VIEW_Z"    ,load_int       ,do_cp_view_z   },

			{"CP_LIGHT_X"   ,load_int       ,do_cp_light_x  },
			{"CP_LIGHT_Y"   ,load_int       ,do_cp_light_y  },
			{"CP_LIGHT_Z"   ,load_int       ,do_cp_light_z  },

			{"GOTO"         ,load_branch    ,do_branch      },
			{"BRANCH"       ,load_branch    ,do_branch      },
			{"BEQ"          ,load_branch    ,do_beq         },
			{"BNEQ"         ,load_branch    ,do_bneq        },
			{"BBIG"         ,load_branch    ,do_bbig        },
			{"BLESS"        ,load_branch    ,do_bless       },

			{"OP_INIT"      ,NULL           ,do_op_init     },
			{"OP_OFF_X"     ,load_var_name  ,do_op_off_x    },
			{"OP_OFF_Y"     ,load_var_name  ,do_op_off_y    },
			{"OP_OFF_Z"     ,load_var_name  ,do_op_off_z    },
			{"OP_DEG_X"     ,load_var_name  ,do_op_deg_x    },
			{"OP_DEG_Y"     ,load_var_name  ,do_op_deg_y    },
			{"OP_DEG_Z"     ,load_var_name  ,do_op_deg_z    },
			{"OP_ZOOM"      ,load_var_name  ,do_op_zoom     },
			{"OP"           ,load_op        ,do_op          },

			{"TRAP"         ,load_trap      ,do_trap        },//new
			{"UNTRAP"       ,load_untrap    ,do_untrap      },//new
			{"DOTRAP"       ,NULL           ,do_dotrap      },

			{"SHOW"         ,load_show      ,do_show        },
			{"VIEWPORT"     ,load_viewport  ,do_viewport    },
			{"FLIPPAGE"     ,NULL           ,do_flippage    },

			{"HIDE"         ,load_element   ,do_hide        },
			{"EXPOSE"       ,load_element   ,do_expose      },

			{"MACRORUN"     ,NULL           ,do_macrorun    },
			{"MACROSTOP"    ,NULL           ,do_macrostop   },
			{"MACRODUMP"    ,load_macrodump ,do_macrodump   },
			{"MACROLOAD"    ,load_macroload ,do_macroload   },

			{"SKY"          ,load_int       ,do_sky         },
			{"GROUND"       ,load_int       ,do_ground      },
			{"BACK"         ,load_int       ,do_back        },

			{"VIEWMOVE"     ,load_vector    ,do_viewmove    },
			{"LIGHTMOVE"    ,load_vector    ,do_lightmove   },
			{"SETVIEW"      ,load_vector    ,do_setview     },
			{"SETLIGHT"     ,load_vector    ,do_setlight    },

			{""             ,NULL           ,NULL           }  };


static struct                   // keystroks trap array
	{
	 FILM *trap_film;
	}
	s_TRAPS[256];


static struct                   // up to 1024 macro keystroks
	{
	 char key;
	 int time;
	}
	s_MACRO[1024];




static struct
	{
	 NAME name;
	 int (*screen)();
	}
	s_screen_commands[]=
			// command name ,screen procedure

		     {  {"VIEWPORT"     ,screen_viewport        },
			{"TEXTXY"       ,screen_textxy          },
			{"BOX"          ,screen_box             },
			{"BACK"         ,screen_back            },
			{"CLEAR"        ,screen_clear           },
			{"LINE"         ,screen_line            },
			{"PAUSE"        ,screen_pause           },
			{"SKY"          ,screen_sky             },
			{"GROUND"       ,screen_ground          },
			{""             ,NULL                   }  };


/****************************************************************************
*                                                                           *
* Procedure:    screen_viewport                                             *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  change viewport position                                    *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_viewport(FILE *f)
{
int left,top,right,bottom;

 read_word(s_line,MAX_LINE,f,UPCASE);
 left=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 top=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 right=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 bottom=str_to_int(s_line);
 my_setviewport(left,top,right,bottom);
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:    screen_textxy                                               *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  write text to the screen.                                   *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_textxy(FILE *f)
{
int color,x,y;

 read_word(s_line,MAX_LINE,f,UPCASE);
 color=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 x=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 y=str_to_int(s_line);

 if(!(!read_word(s_line,MAX_LINE,f,NORMAL) || (s_line[0]==s_COMMAND_PREFIX)))
 {
  my_setcolor(color);
  my_outtextxy(x,y,s_line);
  flip_page();
  my_outtextxy(x,y,s_line);
 }
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    screen_box                                                  *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  draw filled box                                             *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_box(FILE *f)
{
int color,left,top,right,bottom;

 read_word(s_line,MAX_LINE,f,UPCASE);
 color=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 left=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 top=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 right=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 bottom=str_to_int(s_line);
 my_setcolor(color);
 my_bar(left,top,right,bottom);
 flip_page();
 my_bar(left,top,right,bottom);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    screen_back,screen_sky,screen_ground                        *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  change background/sky/ground color                          *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_back(FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 sky_color=str_to_int(s_line);
 ground_color=str_to_int(s_line);
 return;
}

int screen_sky(FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 sky_color=str_to_int(s_line);
 return;
}

int screen_ground(FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 ground_color=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    screen_clear                                                *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  clear current viewport                                      *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_clear(FILE *f)
{
 my_clearviewport();
 flip_page();
 my_clearviewport();
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    screen_line.                                                *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  draw line according to the input detailes.                  *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_line(FILE *f)
{
int color,left,top,right,bottom;

 read_word(s_line,MAX_LINE,f,UPCASE);
 color=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 left=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 top=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 right=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 bottom=str_to_int(s_line);
 my_setcolor(color);
 my_line(left,top,right,bottom);
 flip_page();
 my_line(left,top,right,bottom);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    screen_pause                                                *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  wait until any keys pressed                                 *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int screen_pause(FILE *f)
{
 while (!kbhit());
 return;
}




/***********************
* load time procedures *
***********************/

/****************************************************************************
*                                                                           *
* Procedure:    code_alloc.                                                 *
* ----------                                                                *
* Inputs:       n - size of bytes to allocate.                              *
* -------                                                                   *
* Outputs:      return; - location of memory allocated.                      *
* --------                                                                  *
* Description:  this function is used to get memory quota from segment.     *
* ------------                                                              *
* Date:         21/03/95                                                    *
* -----                                                                     *
****************************************************************************/

char far *code_alloc(int n)
{
char far *temp;

 temp=s_CODE+s_last_code;
 s_last_code+=n;
 return(temp);
}


/****************************************************************************
*                                                                           *
* Procedure:    find_element.                                               *
* ----------                                                                *
* Inputs:       list - the entry location of the first element (list).      *
* -------       name - name of the requested element.                       *
*                                                                           *
* Outputs:      return; the location of the element.                        *
* --------                                                                  *
* Description:  this function is used to find element from element list.    *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

ELEMENT *find_element(ELEMENT *list,NAME *name)
{
ELEMENT *temp;

 temp=list;
 while ((temp!=NULL) && strcmp(name,temp->name)) temp=temp->next;
 return(temp);
}


/****************************************************************************
*                                                                           *
* Procedure:    find_polygon.                                               *
* ----------                                                                *
*                                                                           *
* Inputs:       list - the entry location of the first polygon (list).      *
* -------       name - name of the requested polygon.                       *
*                                                                           *
* Outputs:      return; the location of the polygon.                        *
* --------                                                                  *
* Description:  this function is used to find polygon from polygon list.    *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

POLYGON *find_polygon(POLYGON *list,NAME *name)
{
POLYGON *temp;

 temp=list;
 while ((temp!=NULL) && strcmp(name,temp->name)) temp=temp->next;
 return(temp);
}


/****************************************************************************
*                                                                           *
* Procedure:    search_element.                                             *
* ----------                                                                *
* Inputs:       full path - string "../.../..../....."                      *
* -------                                                                   *
* Outputs:      return; pointer to the element (NULL if not found).         *
* --------                                                                  *
* Description:  this function search in the data structure the last element *
* ------------  in the path name & finds its position.                      *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

ELEMENT *search_element(LINE path)
{
char *temp_name;
ELEMENT *temp;

 temp_name=(char *)strtok(path,s_PATH_SEPARATOR);     // root name
 temp=find_element(s_main_element,temp_name);         // find root index

// from this point - temp_name is son.

 temp_name=(char *)strtok(NULL,s_PATH_SEPARATOR);
 while ((temp!=NULL) && (temp_name!=NULL))
 {
  temp=temp->son;                                     // down to son list
  temp=find_element(temp,temp_name);                  // search son
  temp_name=(char *)strtok(NULL,s_PATH_SEPARATOR);
 }
 return(temp);
}


/****************************************************************************
*                                                                           *
* Procedure:    get_parent.                                                 *
* ----------                                                                *
* Inputs:       full path - string "../.../..../....."                      *
* -------                                                                   *
* Outputs:      return; - parent index of the element in the path.          *
* --------      name   - new element's name.                                *
*                                                                           *
* Description:  this function search in the data structure parent of        *
* ------------  the last element in the path name & finds position.         *
*               the name return;ed is the son of the parent.                *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

ELEMENT *get_parent(LINE path,NAME name)
{
char *temp_name,*temp_next;
ELEMENT *parent_indx,*parent_list;

 temp_name=(char *)strtok(path,s_PATH_SEPARATOR);       // root name
 temp_next=(char *)strtok(NULL,s_PATH_SEPARATOR);

 parent_list=s_main_element;
 parent_indx=NULL;

 while (temp_next!=NULL)
 {
  parent_indx=find_element(parent_list,temp_name);
  parent_list=parent_indx->son;
  temp_name=temp_next;
  temp_next=(char *)strtok(NULL,s_PATH_SEPARATOR);
 }
 strcpy(name,temp_name);
 return(parent_indx);
}


/****************************************************************************
*                                                                           *
* Procedure:    read_element.                                               *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read new element from data file. create new element &       *
* ------------  update the data structure. all polygons used with that      *
*               element are linked.                                         *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int read_element(FILE *f)
{
ELEMENT *temp_element;
ELEMENT *parent;
POLY_ELEM *temp_poly_elem;
ATTRIB attrib;

 if(!read_word(s_line,MAX_LINE,f,UPCASE) || (s_line[0]==s_COMMAND_PREFIX))
   return;

 temp_element=(ELEMENT *)code_alloc(sizeof(ELEMENT));
 temp_element->active_flag=ON;
 temp_element->dirty=OFF;
 temp_element->next=NULL;
 temp_element->son=NULL;
 temp_element->poly_list=NULL;
 parent=get_parent(s_line,temp_element->name);

 if(parent==NULL)
 {
  temp_element->next=s_main_element;    // link the element in the root
  s_main_element=temp_element;
 }
 else
 {
  temp_element->next=parent->son;       // link the element as a son
  parent->son=temp_element;
 }

 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.deg_x=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.deg_y=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.deg_z=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.off_x=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.off_y=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.off_z=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_element->attrib.zoom=str_to_fruc(s_line);
 general_matrix(temp_element->mat,temp_element->attrib);

 // link polygons to the element

 while (read_word(s_line,MAX_LINE,f,UPCASE) && (s_line[0]!=s_COMMAND_PREFIX))
 {
  temp_poly_elem=(POLY_ELEM *)code_alloc(sizeof(POLY_ELEM));
  temp_poly_elem->next=temp_element->poly_list;
  temp_element->poly_list=temp_poly_elem;
  temp_poly_elem->polygon=find_polygon(s_first_polygon,s_line);

// get color of polygon

  read_word(s_line,MAX_LINE,f,UPCASE);
  temp_poly_elem->color=str_to_int(s_line);

// get normal of polygon

  read_word(s_line,MAX_LINE,f,UPCASE);
  temp_poly_elem->normal[X_]=str_to_fruc(s_line);
  read_word(s_line,MAX_LINE,f,UPCASE);
  temp_poly_elem->normal[Y_]=str_to_fruc(s_line);
  read_word(s_line,MAX_LINE,f,UPCASE);
  temp_poly_elem->normal[Z_]=str_to_fruc(s_line);

// get "normal-hiding" flag

  read_word(s_line,MAX_LINE,f,UPCASE);
  temp_poly_elem->hide_normal=str_to_int(s_line);
 }
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    read_polygon.                                               *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read new polygon from data file. create new polygon &       *
* ------------  update the data structure.                                  *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int read_polygon(FILE *f)
{
POLYGON *temp_polygon;
VECTOR  *temp_vector;
int cord=X_;

 if(!read_word(s_line,MAX_LINE,f,UPCASE) || (s_line[0]==s_COMMAND_PREFIX))
   return;
 temp_polygon=(POLYGON *)code_alloc(sizeof(POLYGON));
 strcpy(temp_polygon->name,s_line);
 temp_polygon->next=s_first_polygon;
 s_first_polygon=temp_polygon;
 temp_polygon->vector_no=0;

 (temp_polygon->fill[X_])=0;
 (temp_polygon->fill[Y_])=0;
 (temp_polygon->fill[Z_])=0;

 while (read_word(s_line,MAX_LINE,f,UPCASE) && (s_line[0]!=s_COMMAND_PREFIX))
 {
  if (cord==X_)
   {
    temp_vector=(VECTOR *)code_alloc(sizeof(VECTOR));
    (temp_polygon->vector_no)++;
   }
  (*temp_vector)[cord]=str_to_int(s_line);
  (temp_polygon->fill[cord])+=(*temp_vector)[cord];
  cord=(cord+1) % 3;
 }
 (temp_polygon->fill[X_])/=(FRUC)(temp_polygon->vector_no);
 (temp_polygon->fill[Y_])/=(FRUC)(temp_polygon->vector_no);
 (temp_polygon->fill[Z_])/=(FRUC)(temp_polygon->vector_no);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    read_film.                                                  *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the film commands "#f" from the data file & create the *
* ------------  film data structure. each film command has it's own loader  *
*               & the procedure runs the film command loader.               *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int read_film(FILE *f)
{
FILM *temp_film;
int i=0;

 init_traps();
// init_macro();

 if(!read_word(s_line,MAX_LINE,f,UPCASE) || (s_line[0]==s_COMMAND_PREFIX))
  return;
 while(s_film_commands[i].name[0] && strcmp(s_line,s_film_commands[i].name)) i++;
 if(s_film_commands[i].name[0])
 {
  temp_film=(FILM *)code_alloc(sizeof(FILM));
  temp_film->next=NULL;
  temp_film->command=i;
  if(s_start_command==NULL) s_start_command=temp_film;
  else s_current_command->next=temp_film;
  s_current_command=temp_film;
  if(s_film_commands[i].load_time!=NULL) s_film_commands[i].load_time(temp_film,f);
 }
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    read_remark.                                                *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the film until "##" apears.                            *
* ------------                                                              *
* Date:         12/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int read_remark(FILE *f)
{
FILM *temp_film;


 do
 {
  while(read_word(s_line,MAX_LINE,f,UPCASE) && (s_line[0]!=s_COMMAND_PREFIX));
 }
 while (s_line[1]!=s_COMMAND_PREFIX);
 read_word(s_line,MAX_LINE,f,UPCASE);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    read_file.                                                  *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the commands "#f" / "#e" / "#p" from the data file &   *
* ------------  run the specific command loader.                            *
*                                                                           *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int read_file(FILE *f)
{
FILM *temp1,*temp2;

 s_line[0]='\0';
 do
  if (s_line[0]!=s_COMMAND_PREFIX) read_word(s_line,MAX_LINE,f,UPCASE);
  else
  switch(s_line[1])
  {
   case 'P': read_polygon(f);
	     break;

   case 'E': read_element(f);
	     break;

   case 'F': read_film(f);
	     break;

   case 'S': read_screen(f);
	     break;

   case '#': read_remark(f);
	     break;

   default:  read_word(s_line,MAX_LINE,f,UPCASE);
	     break;
  }
 while(!feof(f));


// post process

// update branch commands according to labels

 temp1=s_start_command;
 while(temp1!=NULL)
 {
  if ((s_film_commands[temp1->command].load_time==load_branch)  ||
      (s_film_commands[temp1->command].load_time==load_event) ||
      (s_film_commands[temp1->command].load_time==load_jump) ||
      (s_film_commands[temp1->command].load_time==load_trap))
  {
   temp2=s_start_command;
   while(temp2!=NULL)
    {
     if((s_film_commands[temp2->command].load_time==load_label) &&
	(!strcmp(temp1->arg2.label,temp2->arg2.label)))
	 temp1->arg2.back=temp2->next;
     temp2=temp2->next;
    }
  }
  temp1=temp1->next;
 }

// update variable commands

 temp1=s_start_command;
 while(temp1!=NULL)
 {
  if ((s_film_commands[temp1->command].load_time==load_cp_var) ||
      (s_film_commands[temp1->command].load_time==load_var_name) ||
      (s_film_commands[temp1->command].load_time==load_add_var))
  {
   temp2=s_start_command;
   while(temp2!=NULL)
    {
     if((s_film_commands[temp2->command].load_time==load_var) &&
	(!strcmp(temp1->arg2.label,temp2->arg2.label)))
	 temp1->arg2.var=temp2;
     temp2=temp2->next;
    }
  }
  temp1=temp1->next;
 }

// update variables commands

 temp1=s_start_command;
 while(temp1!=NULL)
 {
  if ((s_film_commands[temp1->command].load_time==load_jump) ||
      (s_film_commands[temp1->command].load_time==load_add_var))
  {
   temp2=s_start_command;
   while(temp2!=NULL)
    {
     if((s_film_commands[temp2->command].load_time==load_var) &&
	(!strcmp(temp1->arg1.var_name,temp2->arg2.label)))
	 temp1->arg1.var=temp2;
     temp2=temp2->next;
    }
  }
  temp1=temp1->next;
 }

 temp1=s_start_command;
 while(temp1!=NULL)
 {
  if (s_film_commands[temp1->command].load_time==load_var)
  {
   temp1->arg2.first_value=temp1->arg1.value;
  }
  temp1=temp1->next;
 }
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_end.                                                     *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  stop the film                                               *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_end()
{
 s_finish=ON;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_delay.                                                   *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  perform delay to next function.                             *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_delay()
{
 delay(s_current_command->arg1.value);
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    run_film.                                                   *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  run the film from the start.                                *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int run_film()
{
 s_current_command=s_start_command;
 while(!s_finish) s_film_commands[s_current_command->command].run_time();
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_event.                                                 *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the event key & the label to branch.                   *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_event(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 s_current_command->arg1.event_key=s_line[0];
 read_word(s_line,MAX_LINE,f,UPCASE);
 strcpy(temp_film->arg2.label,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_label.                                                 *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the declared label.                                    *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_label(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 strcpy(temp_film->arg2.label,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_showall.                                                 *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  update the screen with new picture & flip the screen        *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_showall()
{
 draw_z_sort(s_main_element);
 flip_page();
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_attrib.                                                *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the element to work on & the attrib parameter to       *
* ------------  operate on it.                                              *
*                                                                           *
* Date:         1st Writing - 16/12/94     Tested - 24/12/94  ran           *
* -----                                                                     *
****************************************************************************/

int load_attrib(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.element=search_element(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.deg_x=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.deg_y=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.deg_z=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.off_x=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.off_y=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.off_z=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.attrib.zoom =str_to_fruc(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_attrib.                                                  *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  operate the attribute on the element.                       *
* ------------                                                              *
* Date:         16/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_attrib()
{
ATTRIB temp_a;

 product_attrib_attrib(s_current_command->arg2.attrib,
		       s_current_command->arg1.element->attrib,
		       temp_a);

 copy_attrib(temp_a,s_current_command->arg1.element->attrib);
 general_matrix(s_current_command->arg1.element->mat,temp_a);
 s_current_command->arg1.element->dirty=ON;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_cycle_xz.                                              *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the element to work on & the attrib parameter to       *
* ------------  operate on it.                                              *
*                                                                           *
* Date:         16/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_cycle_xz(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.element=search_element(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.vector[X_]=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.vector[Z_]=str_to_fruc(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.vector[Y_]=str_to_fruc(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_cycle_xz.                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  cyclic movment of element.                                  *
* ------------                                                              *
* Date:         16/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_cycle_xz()
{
long dist;
long block;
int alpha;
int alpha_mod;
long pos_x;
long pos_z;
long d1;
long d2;
long dist_x;
long dist_z;

 block=s_current_command->arg2.vector[Y_];

 dist_x=s_current_command->arg1.element->attrib.off_x-s_current_command->arg2.vector[X_];
 dist_z=s_current_command->arg1.element->attrib.off_z-s_current_command->arg2.vector[Z_];

 if (max(labs(dist_x),labs(dist_z))>block)
 {
 alpha_mod=(s_current_command->arg1.element->attrib.deg_y+64) % 128 - 64;
 d1=(fruc_mul(block,sin_(alpha_mod))); // sin
 d2=(fruc_mul(block,cos_(alpha_mod))); // cos

 if (labs(dist_x)>block)
  if (dist_x<0)
  {
   s_current_command->arg1.element->attrib.off_x+=d2;
   s_current_command->arg1.element->attrib.off_z+=d1;
  }
  else
  {
   s_current_command->arg1.element->attrib.off_x-=d2;
   s_current_command->arg1.element->attrib.off_z-=d1;
  }
 else
  if (dist_z<0)
  {
   s_current_command->arg1.element->attrib.off_x-=d1;
   s_current_command->arg1.element->attrib.off_z+=d2;
  }
  else
  {
   s_current_command->arg1.element->attrib.off_x+=d2;
   s_current_command->arg1.element->attrib.off_z-=d1;
  }
 }
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_var.                                                   *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  create variable & read it's initial value.                  *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_var(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable name
 strcpy(temp_film->arg2.label,s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable value
 temp_film->arg1.value=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_var,do_add,do_load.                                      *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  update the variable with a value.                           *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_var()
{
 s_current_command->arg1.value=s_current_command->arg2.first_value;
 s_current_command=s_current_command->next;
 return;
}

int do_add()
{
 s_current_command->arg2.var->arg1.value+=s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_load()
{
 s_current_command->arg2.var->arg1.value=s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:    load_jump.                                                  *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the variable name & the branch label.                  *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/


int load_jump(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           /* get variable name */
 strcpy(temp_film->arg1.var_name,s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);           /* get label name */
 strcpy(temp_film->arg2.label,s_line);
 return;
}

/****************************************************************************
*                                                                           *
* Procedure:    do_jzero,do_jnzero.                                         *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  brance if the variable is zero (or less)/                   *
* ------------  brance if the variable is not zero .                        *
*                                                                           *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_jzero()
{
 if(s_current_command->arg1.var->arg1.value<=0)
  s_current_command=s_current_command->arg2.back;
 else
  s_current_command=s_current_command->next;
 return;
}

int do_jnzero()
{
 if(s_current_command->arg1.var->arg1.value>0)
  s_current_command=s_current_command->arg2.back;
 else
  s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_trap.                                                  *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the trap key & the label to branch .                   *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_trap(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 s_current_command->arg1.event_key=s_line[0];
 read_word(s_line,MAX_LINE,f,UPCASE);
 strcpy(temp_film->arg2.label,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_untrap.                                                *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the trap key to disable.                               *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_untrap(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.event_key=s_line[0];
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_trap.                                                    *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  update the trap table with the trap key & the film command  *
* ------------  to brach.                                                   *
*                                                                           *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_trap()
{
 s_TRAPS[s_current_command->arg1.event_key].trap_film=
	s_current_command->arg2.back;

 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_untrap.                                                  *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  update the trap table with the trap key to disable the film *
* ------------  command from braching.                                      *
*                                                                           *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_untrap()
{
 s_TRAPS[s_current_command->arg1.event_key].trap_film=NULL;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_dotrap.                                                  *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  branch to a film command according to the pressed (if any)  *
* ------------  key & the trap table.                                       *
*                                                                           *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_dotrap()
{
char c;

  if (s_macro_on)
   {
    if(kbhit())
     {
      c=upcase(getch());
      if (s_MACRO[s_last_mac_key].time==s_event_time) s_last_mac_key++;
      if (s_TRAPS[c].trap_film!=NULL)
	 s_current_command=s_TRAPS[c].trap_film;
      else
	 s_current_command=s_current_command->next;
     }
    else
     if (s_MACRO[s_last_mac_key].time==s_event_time)
      {
       c=s_MACRO[s_last_mac_key].key;
       s_last_mac_key++;
       if (s_TRAPS[c].trap_film!=NULL)
	 s_current_command=s_TRAPS[c].trap_film;
       else
	 s_current_command=s_current_command->next;
      }
     else s_current_command=s_current_command->next;
   }
  else
   {
    if(kbhit())
     {
      c=upcase(getch());
      if (s_TRAPS[c].trap_film!=NULL)
       {
	s_current_command=s_TRAPS[c].trap_film;

	// update macro key table

	s_MACRO[s_last_mac_key].time=s_event_time;
	s_MACRO[s_last_mac_key].key=(char)c;
	s_last_mac_key++;
       }
      else s_current_command=s_current_command->next;
     }
    else s_current_command=s_current_command->next;
   }
  s_event_time++;                       // increase event time
  return;
}


/****************************************************************************
*                                                                           *
* Procedure:    init_traps.                                                 *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  clear the trap table.                                       *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int init_traps()
{
int i;

 for(i=0;i<256;i++) s_TRAPS[i].trap_film=NULL;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    init_macro                                                  *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  clear the trap table.                                       *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int init_macro()
{
int i;

 for(i=0;i<1024;i++)
 {
  s_MACRO[i].key='\0';
  s_MACRO[i].time=0;
 }
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    read_screen.                                                *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the screen commands "#s" from the data file & create   *
* ------------  the screen looks.                                           *
*                                                                           *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int read_screen(FILE *f)
{
int i=0;

 if(!read_word(s_line,MAX_LINE,f,UPCASE) || (s_line[0]==s_COMMAND_PREFIX))
   return;
 while(s_screen_commands[i].name[0] &&
       strcmp(s_line,s_screen_commands[i].name)) i++;

 if(s_screen_commands[i].name[0]) s_screen_commands[i].screen(f);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_vector.                                                *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the view point offsets                                 *
* ------------                                                              *
* Date:         22/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_vector(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.vector[X_]=(FRUC)str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.vector[Y_]=(FRUC)str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.vector[Z_]=(FRUC)str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_viewmove,do_lightmove,do_setview,do_setlight.            *
* ----------                                                                *
* Inputs:       none                                                        *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  move/set the view/light point.                              *
* ------------                                                              *
* Date:         22/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_viewmove()
{
VECTOR temp;

 add_vector_vector(view,s_current_command->arg1.vector,temp);
 copy_vector(temp,view);
 normal_vector(view,n_view);
 s_current_command=s_current_command->next;
 return;
}

int do_lightmove()
{
VECTOR temp;

 add_vector_vector(light,s_current_command->arg1.vector,temp);
 copy_vector(temp,light);
 normal_vector(light,n_light);
 s_current_command=s_current_command->next;
 return;
}

int do_setview()
{
 copy_vector(s_current_command->arg1.vector,view);
 normal_vector(view,n_view);
 s_current_command=s_current_command->next;
 return;
}

int do_setlight()
{
 copy_vector(s_current_command->arg1.vector,light);
 normal_vector(light,n_light);
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_show.                                                  *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load element path to show.                                  *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_show(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.element=search_element(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_show.                                                    *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  update the current viewport with new data                   *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_show()
{
 draw_z_sort_elem(s_current_command->arg1.element);
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_viewport                                               *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load viewport parameters.                                   *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_viewport(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.viewport.left=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.viewport.top=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.viewport.right=str_to_int(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg2.viewport.bottom=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_viewport.                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  change viewport window & clear it.                          *
* ------------                                                              *
* Date:         26/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_viewport()
{
 my_setviewport(s_current_command->arg2.viewport.left,
		s_current_command->arg2.viewport.top,
		s_current_command->arg2.viewport.right,
		s_current_command->arg2.viewport.bottom);
 my_clearviewport();
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_flippage.                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  flip active & working graphic pages.                        *
* ------------                                                              *
* Date:         27/11/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_flippage()
{
 flip_page();
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_element.                                               *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read element path to hide/expose.                           *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_element(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.element=search_element(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_hide,do_expose.                                          *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  hide/expose element (stop/start drawing it)                 *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_hide()
{
 s_current_command->arg1.element->active_flag=OFF;
 s_current_command=s_current_command->next;
 return;
}

int do_expose()
{
 s_current_command->arg1.element->active_flag=ON;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_macrorun                                                 *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  run the macro buffer insted of keybord.                     *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_macrorun()
{
 s_macro_on=ON;
 s_event_time=0;
 s_last_mac_key=0;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_macrostop                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  stop macro execution.                                       *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_macrostop()
{
 s_macro_on=OFF;
 s_event_time=0;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_macrodump                                              *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load macro dumping parameters.                              *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_macrodump(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get filename
 strcpy(temp_film->arg1.var_name,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_macrodump                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  dump macro buffer to file.                                  *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_macrodump()
{
FILE *f;
int i;

 i=0;
 if((f=fopen(s_current_command->arg1.var_name,"wt"))!=NULL)
 {
  while (i<s_last_mac_key)
  {
   fprintf(f,"%c %d\n",(char)(s_MACRO[i].key),s_MACRO[i].time);
   i++;
  }
  fclose(f);
 }
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_macroload                                              *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load macro file name.                                       *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_macroload(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get filename
 strcpy(temp_film->arg1.var_name,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_macroload                                                *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load macro buffer from file.                                *
* ------------                                                              *
* Date:         27/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_macroload()
{
FILE *f;
int temp_c;
int temp_t;

 s_last_mac_key=0;
 if((f=fopen(s_current_command->arg1.var_name,"rt"))!=NULL)
 {
  while (!feof(f))
  {
   fscanf(f,"%c %d\n",&temp_c,&temp_t);
   s_MACRO[s_last_mac_key].key=temp_c;
   s_MACRO[s_last_mac_key].time=temp_t;
   s_last_mac_key++;
  }
  fclose(f);
 }
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_cp_var.                                                *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the variable & the number to compare to it.            *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_cp_var(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable name
 strcpy(temp_film->arg2.label,s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);           // get value
 temp_film->arg1.value=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_cp_var.                                                  *   *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  compare a number to a variable.                             *    *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_cp_var()
{
 s_diff=s_current_command->arg2.var->arg1.value-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_cp_atof,load_cp_atoi.                                  *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  get element pointer & value to compare.                     *
* ------------                                                              *
*                                                                           *
* Date:         16/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_cp_atof(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);                   // get element
 temp_film->arg2.element=search_element(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);                   // get value
 temp_film->arg1.f_value=str_to_fruc(s_line);
 return;
}

int load_cp_atoi(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);                   // get element
 temp_film->arg2.element=search_element(s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);                   // get value
 temp_film->arg1.value=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedures:   do_cp_deg_x,do_cp_deg_y,do_cp_deg_z,                        *
* -----------   do_cp_off_x,do_cp_off_y,do_cp_off_z,do_cp_zoom.             *
*                                                                           *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  compare a number to element attrib argument.                *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_cp_deg_x()
{
 s_diff=s_current_command->arg2.element->attrib.deg_x-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_deg_y()
{
 s_diff=s_current_command->arg2.element->attrib.deg_y-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_deg_z()
{
 s_diff=s_current_command->arg2.element->attrib.deg_z-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_off_x()
{
 s_diff=s_current_command->arg2.element->attrib.off_x-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_off_y()
{
 s_diff=s_current_command->arg2.element->attrib.off_y-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_off_z()
{
 s_diff=s_current_command->arg2.element->attrib.off_z-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_zoom()
{
 s_diff=s_current_command->arg2.element->attrib.zoom-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}


int do_cp_ctr_x()
{
 s_diff=s_current_command->arg2.element->draw_mat[X_][O_]-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_ctr_y()
{
 s_diff=s_current_command->arg2.element->draw_mat[Y_][O_]-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_ctr_z()
{
 s_diff=s_current_command->arg2.element->draw_mat[Z_][O_]-s_current_command->arg1.f_value;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_add_var.                                               *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read the dest variable & the source variable.               *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_add_var(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable name
 strcpy(temp_film->arg2.label,s_line);
 read_word(s_line,MAX_LINE,f,UPCASE);           // get value
 strcpy(temp_film->arg1.var_name,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_add_var.                                                 *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  add two variables.                                          *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_add_var()
{
 s_current_command->arg2.var->arg1.value+=s_current_command->arg1.var->arg1.value;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_int.                                                   *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read integer number.                                        *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_int(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable value
 temp_film->arg1.value=str_to_int(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedures:   do_cp_view_x,do_cp_view_y,do_cp_view_z,                     *
* -----------   do_cp_light_x,do_cp_light_y,do_cp_light_z.                  *
*                                                                           *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  compare a number to view/light vector argument.             *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_cp_view_x()
{
 s_diff=view[X_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_view_y()
{
 s_diff=view[Y_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_view_z()
{
 s_diff=view[Z_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_light_x()
{
 s_diff=light[X_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_light_y()
{
 s_diff=light[Y_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_cp_light_z()
{
 s_diff=light[Z_]-s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_label.                                                   *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  skip the label to the following command.                    *
* ------------                                                              *
* Date:         27/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_label()
{
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_branch.                                                *  *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the label to branch.                                   *
* ------------                                                              *
* Date:         26/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int load_branch(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 strcpy(temp_film->arg2.label,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_branch,do_beq,do_bneq,do_bbig,do_bless.                  *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  branch (if condition is true) to the label address.         *
* ------------                                                              *
* Date:         26/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_branch()
{
 s_current_command=s_current_command->arg2.back;
 return;
}

int do_beq()
{
 if (!s_diff) s_current_command=s_current_command->arg2.back;
 else s_current_command=s_current_command->next;
 return;
}

int do_bneq()
{
 if (s_diff) s_current_command=s_current_command->arg2.back;
 else s_current_command=s_current_command->next;
 return;
}

int do_bbig()
{
 if (s_diff>0) s_current_command=s_current_command->arg2.back;
 else s_current_command=s_current_command->next;
 return;
}

int do_bless()
{
 if (s_diff<0) s_current_command=s_current_command->arg2.back;
 else s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_event.                                                   *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  if event key is pressed - goto the label address.           *
* ------------  else - continue with next command.                          *
*                                                                           *
* Date:         26/12/94                                                    *
* -----                                                                     *
****************************************************************************/

int do_event()
{
int c;

  if(kbhit())
   {
    if (upcase(getch())==s_current_command->arg1.event_key)
     s_current_command=s_current_command->arg2.back;
    else s_current_command=s_current_command->next;
   }
  else s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_op_init.                                                 *  *
* ---------                                                                 *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  init scrach opertor to zoom=1,no offset & no rotation.      *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_op_init()
{
 s_operator.deg_x=0;
 s_operator.deg_y=0;
 s_operator.deg_z=0;
 s_operator.off_x=0;
 s_operator.off_y=0;
 s_operator.off_z=0;
 s_operator.zoom=IDENT;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_var_name.                                              *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  read variable name                                          *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_var_name(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);           // get variable name
 strcpy(temp_film->arg2.label,s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_op_off_x,do_op_off_y,do_op_off_z,                        *
* ----------    do_op_deg_x,do_op_deg_y,do_op_deg_z,do_op_zoom.             *
*                                                                           *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  add offset/degrees/zoom to scratch operator                 *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_op_off_x()
{
 s_operator.off_x+=inv_adj((long)(s_current_command->arg2.var->arg1.value));
 s_current_command=s_current_command->next;
 return;
}

int do_op_off_y()
{
 s_operator.off_y+=inv_adj((long)(s_current_command->arg2.var->arg1.value));
 s_current_command=s_current_command->next;
 return;
}

int do_op_off_z()
{
 s_operator.off_z+=inv_adj((long)(s_current_command->arg2.var->arg1.value));
 s_current_command=s_current_command->next;
 return;
}

int do_op_deg_x()
{
 s_operator.deg_x+=s_current_command->arg2.var->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_op_deg_y()
{
 s_operator.deg_y+=s_current_command->arg2.var->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_op_deg_z()
{
 s_operator.deg_z+=s_current_command->arg2.var->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_op_zoom()
{
 s_operator.deg_z*=(long)(s_current_command->arg2.var->arg1.value);
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    load_op.                                                    *
* ----------                                                                *
* Inputs:       temp_film - new command in the film structure.              *
* -------       f         - data file.                                      *
*                                                                           *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  load the element to work on.                                *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int load_op(FILM *temp_film,FILE *f)
{
 read_word(s_line,MAX_LINE,f,UPCASE);
 temp_film->arg1.element=search_element(s_line);
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_op.                                                      *
* ----------                                                                *
* Inputs:       none.                                                       *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  operate the attribute on the element.                       *
* ------------                                                              *
* Date:         25/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_op()
{
ATTRIB temp_a;

 product_attrib_attrib(s_operator,
		       s_current_command->arg1.element->attrib,
		       temp_a);

 copy_attrib(temp_a,s_current_command->arg1.element->attrib);
 general_matrix(s_current_command->arg1.element->mat,temp_a);
 s_current_command->arg1.element->dirty=ON;
 s_current_command=s_current_command->next;
 return;
}


/****************************************************************************
*                                                                           *
* Procedure:    do_sky,do_ground,do_back                                    *
* ----------                                                                *
* Inputs:       f - data file.                                              *
* -------                                                                   *
* Outputs:      none.                                                       *
* --------                                                                  *
* Description:  change sky background color                                 *
* ------------                                                              *
* Date:         21/01/95                                                    *
* -----                                                                     *
****************************************************************************/

int do_sky()
{
 sky_color=s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_ground()
{
 ground_color=s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}

int do_back()
{
 ground_color=sky_color=s_current_command->arg1.value;
 s_current_command=s_current_command->next;
 return;
}
