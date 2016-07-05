#include <stdio.h>
#include <string.h>

int ext_sum = 0;

void test()
{
	static int sum = 0;
	sum++;
	printf("sum : %d \r\n", sum);
	ext_sum++;
}
extern int test_num;
//같이 컴파일 하는 것중에 있다고 선언

int main()
{
	test();
	test();

	printf("%d \r\n", ext_sum);

	printf("%d",test_num);

	//printf("%d \r\n",sum);
	//static 정적 변수
	//함수 안에서 쓰면 거기 안에서만 쓸수 있다.
	
	return 0;
}
