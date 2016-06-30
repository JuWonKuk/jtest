#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"

void drawMyBox(int xpos,int ypos,int color)
{
	int ix,iy;
	ix = 1;
	iy = 1;

	setColor(30,color);
	while(ix <= 4 )
	{
		iy = 1;
		while(iy <= 2)
		{	
			gotoxy(ix+xpos,iy+ypos);
			printf(" ");
			iy++;
		}
		ix++;
	}
	setColor(0,0);
}

int main()
{
	system("clear");
	
	drawMyBox(4,2,42);
	drawMyBox(8,4,45);
			
	setColor(30,44); //blue color
	gotoxy(0,40);
	printf("                                  ");
	setColor(0,0);

	return 0;
}
