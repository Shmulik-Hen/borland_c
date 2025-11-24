/*header for this file*/

typedef struct{
	int x,y;
	}POINT;

typedef struct{
	int top,left,right,bottom;
	}RECT;

typedef struct{
	unsigned int type;
	void *next;
	}OBJECTHEAD;

typedef struct{
	OBJECTHEAD head;
	RECT frame;
	char *back;
	}WINDOW;

#define DROPSHADOW 5

void MouseOn();
void MouseOff();
int MouseDownL(struct POINT *p);
int MouseDownR(struct POINT *p);
void MouseLoc(struct POINT *p);
int InitMouse(void);
void ArrowCursor(void);
void WaitCursor(void);
void FingerCursor(void);
void MoveMouse(struct POINT *p);





