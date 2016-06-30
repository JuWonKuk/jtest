#include <stdio.h>
#include <stdlib.h>

void setColor(int fore_color,int backg_color)
{
	printf("%c[%d;%dm",0x1b, fore_color, backg_color);
}

void gotoxy(int x, int y)
{
	printf("%c[%d;%df",0x1b, y, x);	
}

int main()
{
	system("clear");
	//"\x1b[31m"
	//printf("%c[%dm",0x1b, fore_color);
	
	printf("*********************************************");

	gotoxy(17,3);
	setColor(33,44);
	printf("hello");

	gotoxy(17,5);
	setColor(32,43);
	printf("hello");
	setColor(0,0); //reset ansi command
	
	gotoxy(45,2);
	setColor(31,40);
	printf("*");
	gotoxy(0,2);
	printf("*");

	gotoxy(45,3);
	setColor(31,2);
	printf("*");
	gotoxy(0,3);
	printf("*");
	
	gotoxy(45,4);
	setColor(33,40);
	printf("*");
	gotoxy(0,4);
	printf("*");
	
	gotoxy(45,5);
	setColor(32,40);
	printf("*");
	gotoxy(0,5);
	printf("*");
	
	gotoxy(45,6);
	setColor(34,40);
	printf("*");
	gotoxy(0,6);
	printf("*");
	gotoxy(2,6);
	printf("□□□□□■■■■■■■■■□□□□□□□□□□□□□□□□■■■■■■■■■□□□□");

	gotoxy(45,7);
	setColor(34,2);
	printf("*");
	gotoxy(0,7);
	printf("*");
	gotoxy(2,7);
	printf("□□□□■■■■■■■■■■□□□□□□□□□□□□□□□■■■■■■■■□■■□□□");

	gotoxy(45,8);
	setColor(35,2);
	printf("*");
	gotoxy(0,8);
	printf("*");
	gotoxy(2,8);
	printf("□□□□■■■■■■■■■■■□□□□□□□■□■■□□■■■■■■■■□□□■■□□");
	
	gotoxy(45,9);
	setColor(31,40);
	printf("*");
	gotoxy(0,9);
	printf("*");
	gotoxy(2,9);
	printf("□□□■■□□□□■■■■■■□■□■■□■■■■□□■■■■■■□□□□□□■■□□");

	gotoxy(45,10);
	setColor(31,2);
	printf("*");
	gotoxy(0,10);
	printf("*");
	gotoxy(2,10);
	printf("□□□■■□□□□□■■■■■■■■■■■■■■■■■■■■■■□□□□□□□■■□□");

	gotoxy(45,11);
	setColor(33,40);
	printf("*");
	gotoxy(0,11);
	printf("*");
	gotoxy(2,11);
	printf("□□□■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■□□□□□□■■□□");

	gotoxy(45,12);
	setColor(32,40);
	printf("*");
	gotoxy(0,12);
	printf("*");
	gotoxy(2,12);
	printf("□□□■■□□□□□■■■■■■■■■■■■■■■■■■■■■■■□□□□□□■■□□");

	gotoxy(45,13);
	setColor(34,40);
	printf("*");
	gotoxy(0,13);
	printf("*");
	gotoxy(2,13);
	printf("□□□□■■□□□■□■■■■■■■■■■■■■■■■■■■■■■□□□□□□■■□□");

	gotoxy(45,14);
	setColor(34,2);
	printf("*");
	gotoxy(0,14);
	printf("*");
	gotoxy(2,14);
	printf("□□□□■■□□■□□□□□□□■■■■■■■■■■■■■■■■■■■□□□□■■□□");

	gotoxy(45,15);
	setColor(35,2);
	printf("*");
	gotoxy(0,15);
	printf("*");
	gotoxy(2,15);
	printf("□□□□□■■■□□□□■■■■■■□□■■■■■■■■■■■■■■■■□□□■■□□");
	
	setColor(0,0);
	gotoxy(0,16);
	printf("*********************************************");
	
	return 0;
}
