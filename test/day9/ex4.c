#include <stdio.h>

int main()
{
	int test = 0x0000001; // 0000 0001
	test = test << 1; 
	// 왼쪽 한칸 이동 0000 0010 / 0000 0100 / 0000 1000
	// 왼쪽 *2 / 오른쪽 / 2
	printf("%x \r\n",test);

	return 0;
}
