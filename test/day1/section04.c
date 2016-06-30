#include <stdio.h>
#include <stdlib.h>

int main()
{
	system("clear");
	
	

	printf("\x1b[3;3f");
	printf("hello");
	printf("\x1b[5;2f");
	printf("hello");
	printf("\x1b[3;15f");
	printf("*");
	printf("\x1b[4;15f");
	printf("*");
	printf("\x1b[5;15f");
	printf("*");
	printf("\x1b[6;15f");
	printf("*");
	printf("\x1b[7;15f");
	printf("*");

	printf("\x1b[20;0f");
	printf("====================");
	return 0;
}
