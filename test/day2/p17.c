#include <stdio.h>

int main()
{
	int num1;
	
	printf("input :");
	scanf("%d", &num1);
	if(num1 > 5)
		printf("5보다 큽니다.");
	else if(num1 < 5)
		printf("5보다 작습니다.");
	else
		printf("5와 같습니다.");

	return 0;
}
