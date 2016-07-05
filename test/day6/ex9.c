#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//add 10,20
	//sub 5,2
	//mul 4,3
	//div 8,2
	
	char strCmd[128];

	gets(strCmd);

	int a,b;
	//char *pCmd;
	char *ptrTemp;

	ptrTemp = strtok(strCmd," ");
	a = atoi( strtok(NULL,","));
	b = atoi( strtok(NULL,","));
	
	//pCmd = strdup(ptrTemp);

	if(strcmp(ptrTemp,"add") == 0)
		printf("%d + %d = %d \r\n",a,b,a+b);
	else if(strcmp(ptrTemp,"sub") == 0)
		printf("%d - %d = %d \r\n",a,b,a-b);	
	else if(strcmp(ptrTemp,"mul") == 0)
		printf("%d * %d = %d \r\n",a,b,a*b);	
	else if(strcmp(ptrTemp,"div") == 0)
		printf("%d / %d = %d \r\n",a,b,a/b);	

	

	return 0;
}
