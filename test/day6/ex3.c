#include <stdio.h>

int main()
{
	char aStr[] = "world";
	char *pStr = "hello";
	
	printf("%s %s \r\n",aStr,pStr);	
	
	pStr = aStr;

	printf("%s \r\n", pStr);

	//aStr = pStr;
	// 배열은 상수값, 포인터는 주소값
	//printf("%s \r\n", aStr);

	return 0;
}
