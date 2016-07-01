#include <stdio.h>

int num1 = 7; //전역 변수

void test()
{
	printf("%d \r\n", num1);
}

int main()
{
	int num1 = 3;

	{	//{ } 다른 공간
		//int num1 = 4;
		//상위 변수를 참조
		num1 = 4;
		printf("%d \r\n", num1);
	}

	printf("%d \r\n", num1);
	test();

	return 0;
}
