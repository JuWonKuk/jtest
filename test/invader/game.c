#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"

#include "bullet.h"
#include "plane.h"
#include "alien.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;
_S_MAP_OBJECT gAlienModel;

_S_BULLET_OBJECT gBulletObjects[32];
_S_ALIEN_OBJECT gAlienObjects[8];
_S_Plane gPlayerObject;

int main()
{

	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],70,32);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");
	
	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");
	
	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	for(int i=0;i <32;i++) {
		bullet_init(&gBulletObjects[i],0,0,0,&gBulletModel);
	}
	for(int i=0;i <8;i++) {
		alien_init(&gAlienObjects[i],&gAlienModel);

		gAlienObjects[i].m_fXpos = i+(i+5+(i+3+(i+1)) );
		gAlienObjects[i].m_fYpos = 2;
		gAlienObjects[i].m_nFSM = 1;
	}

	
	Plane_init(&gPlayerObject,&gPlayerModel,17,10);
		
	set_conio_terminal_mode();
	acc_tick=last_tick=0;

	system("clear");
	while(bLoop) {
		//타이밍처리 
		clock_gettime(CLOCK_MONOTONIC,&work_timer);
		double cur_tick = work_timer.tv_sec + 
			(double)(work_timer.tv_nsec * 1e-9);
		double delta_tick = cur_tick - last_tick;
		last_tick = cur_tick;
		//실시간 입력
		if(kbhit() != 0) {
			char ch = getch();
			if(ch == 'q') {
				bLoop = 0;
				puts("bye~ \r");
			}
			
		}
		for(int i =0;i<8;i++) {
			gAlienObjects[i].pfApply(&gAlienObjects[i],delta_tick);
		}
		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			//puts("tick...\r");
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			for(int i=0;i <8;i++) {
				gAlienObjects[i].pfDraw(&gAlienObjects[i],&gScreenBuf[1]);
			}
		
			map_dump(&gScreenBuf[1],Default_Tilepalette);
			acc_tick = 0;
		}

	}

	return 0;

}
