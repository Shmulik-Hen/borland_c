
#include <dos.h>
#include <string.h>

static union REGS r;
static struct SREGS s;

struct {
   char sig [4];    /* Should contain "VESA" */
   unsigned char hi_ver;
   unsigned char low_ver;
   char far *manufact;  /* ptr to manufacturer name */
   unsigned long flag;  /* capabilities of card */
   char far *modelist;
   char pad [240];
} vesa_header;


int vesa_detect () {

    r.x.ax = 0x4f00;
    r.x.di = FP_OFF (&vesa_header);
    s.es   = FP_SEG (&vesa_header);

    int86x (0x10, &r, &r, &s);
    if (r.x.ax != 0x004f)
	return (0);
    if (strncmp (vesa_header.sig, "VESA", 4 ) )
	return (0);
     return (1);
}


void main () {

    printf ( "\n%d", vesa_detect () );
    if (!vesa_detect() ) {
	printf ("\nVESA Driver not detected.");
    } else {
	printf ("\nVESA driver detected.");
	printf ("\nManufacture  : %s", vesa_header.manufact );
	printf ("\nVESA version : %d.%d", vesa_header.hi_ver,
					  vesa_header.low_ver);



     }
}


