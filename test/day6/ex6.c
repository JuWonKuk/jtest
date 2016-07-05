#include <stdio.h>
#include <string.h>
int main()
{
	char *pStrCmd = "move position 123,56";

	char *ptr = strstr(pStrCmd,"z");
	//strstr 특정 문자열(문자)부터 복사한다.
    //특정 문자열(문자)이 없으면 null
	
	printf("%s \r\n", ptr);

	char pStrTemp[128];
	
	strncpy(pStrTemp,pStrCmd,4);
	//strncpy 해당 갯수만큼 카피
	
	printf("%s \r\n",pStrTemp);

	char *pStrClone;
	//char pstrClone[128];

	pStrClone = strdup(pStrCmd);
	//strcpy 와 비슷 but 
	//  "    는 메모리를 미리 할당한 후 사용한다.
	//strdup 는 자동으로 할당한다.

	pStrClone[0] = 'a';
	//pStrClone = pStrCmd;

	//pStrCmd[1] = 'n';

	printf("%s \r\n", pStrClone);
	printf("%s \r\n", pStrCmd);
	
	return 0;
}
