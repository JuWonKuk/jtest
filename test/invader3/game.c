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
//double acc_guid_delay_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;
_S_MAP_OBJECT gBulletModel2;
_S_MAP_OBJECT gAlienModel;


_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[32];
_S_BULLET_OBJECT gBulletObjects2[32];
_S_ALIEN_OBJECT gAlienObjects[4];


int main()
{

	for(int i=0;i<4;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,48);
	}
	//비행기 
	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");
	//외계인 총알
	map_init(&gBulletModel);
	map_load(&gBulletModel,"plasma.dat");
	//비행기 총알
	map_init(&gBulletModel2);
	map_load(&gBulletModel2,"plasma.dat");
	//외계인
	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");
	
	//외계인 초기화 및 위치,총알
	double TablePosition[] = {0,6,12,18};
	for(int i=0;i<4;i++) {
		_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos = TablePosition[i];
		pObj->m_fYpos = 2;
		pObj->m_nFSM = 1;
		pObj->m_pBullet = &gBulletObjects[i];
		//gBulletObjects[i].m_nFSM = 1;
	}
	//외계인 총알 초기화
	for(int i =0;i<32;i++) {
		_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
		bullet_init(pObj,0,0,0,&gBulletModel);
	}
	//비행기 총알 초기화
	for(int i =0;i<32;i++) {
		_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
		bullet_init(pObj,0,0,0,&gBulletModel2);
		//gPlayerObject.m_pBullet = &gBulletObjects2[i];	
		//pObj->m_nFSM = 1;
	}
	//비행기 초기화
	Plane_init(&gPlayerObject,&gPlayerModel,17,40);
	//비행기(1,화면출력)
	gPlayerObject.m_nFSM = 1;
	//gBulletObjects->m_nFSM = 1;
	
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
			else if(ch == 'j') {
				//비행기 Fire
				for(int i=0;i<32;i++) {	
					_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
					
					//pObj->m_nFSM = 1;
					if(pObj->m_nFSM == 0) {
						pObj->pfFire(pObj,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,
						10,0,-1,5.0);
						break;
					
						
					}
				 }
			}
			//비행기 Apply
			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
	
		}
		//외계인 Apply
		for(int i=0;i<4;i++ ) 
		{
			_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
			pObj->pfApply(pObj,delta_tick);
		}
		
		//외계인 총알 Apply
		for(int i=0;i<32;i++) {
			_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
			pObj->pfApply(pObj,delta_tick);
		}
		//비행기 총알 Apply
		for(int i=0;i<32;i++) {
			_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
			pObj->pfApply(pObj,delta_tick);
		}

		//외계인 총알이 비행기 맞았을때
		for(int i=0;i<32;i++) {
			if(gBulletObjects[i].m_nFSM != 0) {
				double bullet_posx=gBulletObjects[i].m_fXpos;
				double bullet_posy=gBulletObjects[i].m_fYpos;

				double target_posx=gPlayerObject.m_fXpos;
				double target_posy=gPlayerObject.m_fYpos;

				double vx=target_posx-bullet_posx;
				double vy=target_posy-bullet_posy;

				double dist=sqrt(vx*vx+vy*vy);

				if(dist<0.1) {
					//gBulletObjects[i].m_nFSM=0;
					gPlayerObject.m_nFSM=0;
					gBulletObjects2[i].m_nFSM=0;
					//gAlienObjects[i].m_pBullet = NULL;
					
				}
			}
		}
		//비행기 총알이 외계인 맞았을때
		for(int i=0;i<32;i++) {
			if(gBulletObjects2[i].m_nFSM != 0) {
				double target_posx=gAlienObjects[i].m_fXpos;
				double target_posy=gAlienObjects[i].m_fYpos;

				double bullet_posx=gBulletObjects2[i].m_fXpos;
				double bullet_posy=gBulletObjects2[i].m_fYpos;

				double vx=bullet_posx-target_posx;
				double vy=bullet_posy-target_posy;

				double dist=sqrt(vx*vx+vy*vy);

				if(dist<0.5) {
					gBulletObjects[i].m_nFSM=0;
					gAlienObjects[i].m_nFSM = 0;
					//gBulletObjects2[i].m_nFSM=0;
					//gAlienObjects[i].m_pBullet = NULL;

				}
			}
		}


		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			for(int i=0;i<32;i++) {
				_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}
			
			for(int i=0;i<32;i++) {
				_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);
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
