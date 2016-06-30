#include <stdio.h>
#include <stdlib.h>
#include "../engine2d.h"

int main()
{
	system("clear");

	int i =1;
	while(i<10)
	{
		/* 십자가
		gotoxy(5,i);
		printf("+");
		gotoxy(i,5);
		printf("+");
		i++;
		*/
		//X자
		gotoxy(i,i);
		printf("+");
		gotoxy(10-i,i);
		printf("+");
		i++;
		
	}

	gotoxy(0,20);
	printf("===================");
	return 0;
}
