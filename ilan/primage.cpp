#include <graphics.h>
#include <stdio.h>
#include <io.h>
#include <bios.h>

#define		ESCG		'\x1B'
#define		LPT1		0
#define		LPT2		1
#define		prn_putc(x)	biosprint(0,(x),LPT1)

int printimage(int x1, int y1, int x2, int y2);

/*
    Sets Epson printer to bit image mode.
    N is the number of bytes to print.
*/
static void bitImage(int N)
{
    register int	n1, n2;

    n2 = N >> 8;
    n1 = N - (n2 << 8);

	prn_putc(ESCG);
	prn_putc('*');
	prn_putc(4);
	/* K=standard density,  L=double density,
	   Y=dbl speed + dbl density, Z=quad density*/
    prn_putc(n1);
    prn_putc(n2);
}

/*
    Get pixels from the screen and convert them to
    the printer's pin order.
*/
static unsigned char getScrBits(int x, int y)
{
    unsigned char firePins;

    firePins  = (getpixel(x, y++)<6)? 0: 0x80;
    firePins |= (getpixel(x, y++)<6)? 0: 0x40;
    firePins |= (getpixel(x, y++)<6)? 0: 0x20;
    firePins |= (getpixel(x, y++)<6)? 0: 0x10;
    firePins |= (getpixel(x, y++)<6)? 0: 0x08;
    firePins |= (getpixel(x, y++)<6)? 0: 0x04;
    firePins |= (getpixel(x, y++)<6)? 0: 0x02;
    firePins |= (getpixel(x, y  )<6)? 0: 0x01;

    return	firePins;
}

int printimage(int x1, int y1, int x2, int y2)
{
	union REGS r;
    int		x, y, width;

    width = x2-x1;

    for (y=y1; y<y2; y+=8)
    {
		prn_putc(ESCG);
		prn_putc('1'); /* Initialize line spacing to 7/72" */

		bitImage(width);

		for (x=x1; x<x2; x++)
			prn_putc(getScrBits(x,y));

		prn_putc('\n');
    }
    prn_putc(12);
    return	0;
}

