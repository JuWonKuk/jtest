#ifndef __RGAME_H__
#define __RGAME_H__

void drawGamea(int mx, int my, char *pBuf)
{
	//렌더링
	gotoxy(1,1);
	int x, y;
	for(y = 0;y < my; y++)
	{
		for(x = 0;x < mx; x++)
		{
			switch(pBuf[mx * y + x])
			{
				case 0:
					putchar('.');
					break;
				case 1:
					putchar('#');
					break;
				case 2:
					putchar('A');
					break;
			}
		}
		printf("\r\n");
	}

}

#endif
