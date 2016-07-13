#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "map.h"

_S_MAP_OBJECT MapObject;

int main()
{
	int bLoop = 1;

	MapObject.m_header.m_nSkima = 1;
	MapObject.m_pBuf = NULL;
	//char TilePalette[] = {'.','#','@','%'};
	puts("text TileMap Editor v1.1");

	while(bLoop)
	{
		char szCmd[32];
		gets(szCmd);
		char *pTemp = strtok(szCmd," ");
		if(!strcmp(pTemp,"exit")) {
			bLoop = 0;
			if( MapObject.m_pBuf ) {
				free(MapObject.m_pBuf);
			}
		}
		else if(!strcmp(pTemp,"dump")) {
			map_dump(&MapObject,Default_Tilepalette);
		}
		else if(!strcmp(pTemp,"new")) {
			int nWidth = atoi(strtok(NULL," "));
			int nHeight = atoi(strtok(NULL," "));
			map_new(&MapObject,nWidth,nHeight);
		}
		else if(!strcmp(pTemp,"put")) {
			//put 1 2 2 (x y tile_index)
			int x,y,tile_index;
			x = atoi(strtok(NULL," "));
			y = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));
			
			//MapObject.m_pBuf[y*MapObject.m_header.m_nWidth + x] = tile_index ;
			map_PutTile(&MapObject,x,y,tile_index);
		}
		else if(!strcmp(pTemp,"hline")) {
			int xpos,tile_index;
			xpos = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));
			
			for(int iy =0;iy <MapObject.m_header.m_nHeight;iy++) {
				MapObject.m_pBuf[iy*MapObject.m_header.m_nWidth +xpos] = tile_index;
			}
		}
		else if(!strcmp(pTemp,"vline")) {
			int ypos,tile_index;
			ypos = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));

			for(int ix = 0;ix < MapObject.m_header.m_nWidth;ix++) {
				MapObject.m_pBuf[ix + ypos*MapObject.m_header.m_nWidth] = tile_index;
			}
		}
		else if( !strcmp(pTemp,"save")) {
			//save filename
			char *pTemp = strtok(NULL," ");
			map_save(&MapObject,pTemp);
			puts("save ok");
		}
		else if( !strcmp(pTemp,"load")) {
			//load filename
			char *pTemp = strtok(NULL," ");
			map_load(&MapObject,pTemp);
			puts("load ok");
		
		}
		else if(!strcmp(pTemp,"tridraw_1")) {
			//tridraw_1 1
			int tile_index = atoi(strtok(NULL," "));
			for(int y = 0;y < MapObject.m_header.m_nHeight;y++) {
				for(int x = 0;x < y+1 ;x++) {
					MapObject.m_pBuf[y*MapObject.m_header.m_nWidth + x] = tile_index;
				}
			}
		}
		else if(!strcmp(pTemp,"draw_cross")) {
			//draw_cross 1 2 1
			int x,y,tile_index;
			x = atoi(strtok(NULL," "));
			y = atoi(strtok(NULL," "));
			tile_index = atoi(strtok(NULL," "));
			for(int iy =-1;iy <2;iy++) {
				for(int ix=-1;ix < 2;ix++) {
					MapObject.m_pBuf[(iy+y)*MapObject.m_header.m_nHeight + x] = tile_index;
					MapObject.m_pBuf[y*MapObject.m_header.m_nWidth +(ix+x)] = tile_index;

				}
			}

		}

	}

	return 0;
}
