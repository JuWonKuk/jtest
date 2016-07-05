#include <stdio.h>
#include <string.h>

int main()
{
	char strCmd[128];
	//scanf("%s",strCmd);
	gets(strCmd);
	//printf("%s \r\n",strCmd);

	puts(strCmd);
	
	char ch = getchar();
	putchar(ch);

	return 0;
}
