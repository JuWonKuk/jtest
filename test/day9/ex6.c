#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *m_szName;
	void *node[8];
} _S_AREA;

int main()
{
	_S_AREA town = {
		"town",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA dungeon_1 = {
		"dungeon-1",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};
	_S_AREA dungeon_2 = {
		"dungeon-2",
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
	};

	town.node[0] = &dungeon_1;
	dungeon_1.node[0] = &town;
	town.node[1] = &dungeon_2;

	_S_AREA *pCurrentArea = &town;
	
	int bLoop = 1;
	while(bLoop) {
		char szCmd[32];
		gets(szCmd);
		char *pTemp = strtok(szCmd," ");

		if(!strcmp(pTemp,"look")) {
			printf(" 당신은 %s 에 서 있습니다. \r\n",pCurrentArea->m_szName);		
		}
		else if(!strcmp(pTemp,"move")) {
			char *pszArea = strtok(NULL,"");
			printf("당신은 %s 으로 이동합니다. \r\n",pszArea);
			for(int i = 0;i <8;i++) {
				_S_AREA *pNode = pCurrentArea->node[i];
				if(pNode == NULL) break;
				//puts(pNode->m_szName);
				if(!strcmp(pNode->m_szName,pszArea)) {
					printf("이동성공 \r\n");
					pCurrentArea = pNode;
				}
		
			}

		}
		else if(!strcmp(pTemp,"help")) {
			char *pszArea = strtok(NULL,"");
			printf("당신은 %s 으로 이동합니다. \r\n",pszArea);
			for(int i = 0;i <8;i++) {
				_S_AREA *pNode = town->node[i];
				if(pNode == NULL) break;
				else {
					printf("이동목록: %s \r\n",pNode);
				}
				
		else if(!strcmp(pTemp,"exit")) {
			bLoop = 0;
		}
	}

}
