#include <stdio.h>

void str_prn(char **b,int count)
{
	for(int i = 0; i < count; i++)
		printf("%s \r\n", b[i]);
}

int main()
{
	char *ptr_ary[] = {"eagle", "tiger", "lion", "squirrel"};
	int count;

	count = sizeof(ptr_ary)/sizeof(ptr_ary[0]);
	
	str_prn(ptr_ary, count);

	return 0;
}
