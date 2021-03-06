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

#include "plane.h"
#include "bullet.h"
#include "alien.h"

struct timespec work_timer;
double acc_tick,last_tick;
double acc_guid_delay_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;
_S_MAP_OBJECT gAlienModel;

_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[32];
_S_ALIEN_OBJECT gAlienObjects[4];


int main()
{

	for(int i=0;i<2;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,48);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");
	
	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");
	
	Plane_init(&gPlayerObject,&gPlayerModel,17,40);

	double TablePosition[] = {0,6.0,12,18};

	for(int i=0;i<4;i++)
	{
		_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos = TablePosition[i];
		pObj->m_fYpos = 2;
		pObj->m_nFSM = 1;
	}
	for(int i=0;i<32;i++) {
		_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
		bullet_init(pObj,0,0,0,&gBulletModel);	
	}
	
	system("clear");
	
	set_conio_terminal_mode();
	acc_tick=last_tick=0;

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
			else if(ch ='j') {



			}
			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
			for(int i=0;i<32;i++) {
				_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
				pObj->pfApply(pObj,delta_tick);
			}
		}
			for(int i=0;i<4;i++ ) 
			{
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfApply(pObj,delta_tick);

			}
		
		acc_guid_delay_tick += delta_tick;
		if(acc_guid_delay_tick > 2.5) {
			acc_guid_delay_tick = 0;
			for(int i=0;i<32;i++) {
				
				double bullet_pos_x = gBulletObjects[i].m_fXpos;
				double bullet_pos_y = gBulletObjects[i].m_fYpos;

				double target_pos_x = gPlayerObject.m_fXpos;
				double target_pos_y = gPlayerObject.m_fYpos;

				double vx = target_pos_x - bullet_pos_x;
				double vy = target_pos_y - bullet_pos_y;
				double dist = sqrt(vx*vx + vy*vy);
				vx /=dist; vy /=dist;
	
				gBulletObjects[i].m_fvx = vx;
				gBulletObjects[i].m_fvy = vy;

				gBulletObjects[i].m_nFSM = 1;

				gBulletObjects[i].pfFire(&gBulletObjects[i],bullet_pos_x,bullet_pos_y,vx,vy,10.0,10);
				acc_guid_delay_tick = 0;
			}

		}
		for(int i=0;i<32;i++) {
			gBulletObjects[i].pfApply(&gBulletObjects[i],delta_tick);

		}

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);	
			for(int i=0;i<32;i++) {
				
				gBulletObjects[i].pfDraw(&gBulletObjects[i],&gScreenBuf[1]);	
			}
			
			for(int i=0;i<4;i++ ) 
			{
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			map_dump(&gScreenBuf[1],Default_Tilepalete);
			acc_tick = 0;
		}

	}

	return 0;

}

