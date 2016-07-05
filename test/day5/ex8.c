#include <stdio.h>

int main()
{
	int num[] = {3,6,4,5,7};
	int *pNum = num;
	int max = -999;
	int min = 999;
	int sum = 0;

	printf("%d,%d \r\n",*(pNum+1), num[1]);
	
	for(int i = 0;i < sizeof(num)/sizeof(int);i++)
	{
		printf("%d , ",*(pNum+i) );
		sum += *(pNum +i);
		if(max < *pNum + i)
		{
			max = *(pNum+i);
		}
		else if(min > *pNum + i)
		{
			min = *(pNum + i);
		}
	}
	printf("\r\n");
	printf("%d \r\n",sum);
	printf("%d \r\n",max);
	printf("%d \r\n",min);

	return 0;
}
