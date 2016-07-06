#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int bLoop = 1;
	char *strLine[128] = {0};
	int nTalilIndex = 0;
	while(bLoop)
	{
		char *pTemp;
		char strCmd[128];
		gets(strCmd);
		
		pTemp = strtok(strCmd," ");

		if(!strcmp(pTemp,"exit")) {
			bLoop = 0;
		}
		else if(!strcmp(pTemp,"push")) {	
			//push 원하는 문자열
			pTemp = strtok(NULL,"");

			char *pstr = (char *)malloc(strlen(pTemp) +1);
			strcpy(pstr, pTemp);
			strLine[nTalilIndex++] = pstr;
		}
		else if(!strcmp(pTemp,"pop")) {
			nTalilIndex--;
			free(strLine[nTalilIndex]);
			strLine[nTalilIndex] = 0x00;
				
		}
		else if(!strcmp(pTemp,"del")) {
			free(strLine[0]);
			for(int i = 0; i < nTalilIndex+1; i++ ) {
				strLine[i] = strLine[i+1];
			}
		}
		else if(!strcmp(pTemp,"ins")) {
			//ins 2 hello
			int nIndex = atoi(strtok(NULL," "));
			pTemp = strtok(NULL,"");
			int i;
			//printf("%d , %s 추가 \r\n",nIndex,pTemp);
			for(int i = nTalilIndex; i > nIndex; i--) {
				strLine[i] = strLine[i-1];
			}
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			strLine[i] = pstr;
			nTalilIndex++;
		}
		else if(!strcmp(pTemp,"rm")) {
			int nIndex = atoi(strtok(NULL,""));
			free(strLine[nIndex]);
			for(int i = nIndex; i < nTalilIndex ; i++) {
				strLine[i] = strLine[i+1];
			}
			nTalilIndex--;
			strLine[nTalilIndex] = 0x00;
		}
		else if(!strcmp(pTemp,"set")) {
			//set 1 new string
			int nIndex = atoi(strtok(NULL," "));
			free(strLine[nIndex]);
			pTemp = strtok(NULL,"");
			char *pstr = (char *)malloc(strlen(pTemp)+1);
			strcpy(pstr,pTemp);
			strLine[nIndex] = pstr;
		}
		else if(!strcmp(pTemp,"dump")) {
			
			puts("-------------------");
			for(int i = 0; strLine[i] != 0x00; i++) {
				puts(strLine[i]);
			}
			puts("-------------------");
		}
	}

	return 0;
}
