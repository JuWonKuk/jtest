#include <stdio.h>
#include <string.h>

struct _S_HUMAN {
	int m_nHp;
	int m_nMp;
	int m_nLevel;
	double m_dbAp;
	char m_szName[128];	
};


int main()
{
	struct _S_HUMAN human;

	human.m_nHp = 100;
	human.m_nMp = 50;
	human.m_nLevel = 1;
	human.m_dbAp = 3.5;
	strcpy(human.m_szName,"athuer");
	
	printf("hp : %d \r\n",human.m_nHp);	
	return 0;
}
