#include <stdio.h>

int main()
{
	char str1[] = "hello world";
	char str2[80];
	
	int i;
	for(int i = 0;i < str1[i] != 0x00;i++)
	{
		str2[i] = str1[i];
	}

	str2[i] = 0x00;
	

	printf("%s \r\n", str2);

	
}
