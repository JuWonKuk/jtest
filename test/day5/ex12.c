#include <stdio.h>

int main()
{
	char cmd;
	int bLoop;
	char buffer[64];
	char *cbuffer = &buffer;
	int nTailIndex = 0;
	

	for(int i = 0;i < 64; i++)
		cbuffer[i] = 0;
			
	bLoop = 1;
	while(bLoop)
	{
		scanf("%c", &cmd);
		getchar();

		switch(cmd)
		{
			case 'a': //add
				printf("what : ");
				scanf("%c",&cmd);
				getchar();
				cbuffer[nTailIndex] = cmd;
				nTailIndex++;
				break;
			case 'd': 
				nTailIndex--;
				cbuffer[nTailIndex] = 0x00;
				break;
			case 'f':
				for(int i = 0;i < nTailIndex-1;i++)
					cbuffer[i] = cbuffer[i+1];
				nTailIndex--;
				cbuffer[nTailIndex] = 0x00;
				break;
			case 's':
				printf("%s \r\n",cbuffer);
				break;
			case 'q':
				printf("quit \r\n");
				bLoop = 0;
				break;
		}
	}

	return 0;
}
