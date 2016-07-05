#include <stdio.h>

int main()
{
	int ary[5] = {1,2,3,4,5};
	int ary2[5];
	int *pAry;
	
	pAry = ary; // 0

	printf("%d %d\r\n", pAry[1], *ary+1);
	//ary2 = ary; 배열은 읽는 것만 됨 x
	//포인터는 읽고 쓰기가 모두 됨

	return 0;	
}
