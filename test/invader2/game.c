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

void getDirection(_S_BULLET_OBJECT *pBullet,_S_Plane *pPlane,double *_vx,double *_vy ) 
{
	double bullet_pos_x = pBullet->m_fXpos;
	double bullet_pos_y = pBullet->m_fYpos;

	double target_pos_x = pPlane->m_fXpos;
	double target_pos_y = pPlane->m_fYpos;

	double vx = target_pos_x - bullet_pos_x;
	double vy = target_pos_y - bullet_pos_y;
	double dist = sqrt(vx*vx + vy*vy);
	vx /=dist; vy /=dist;
	*_vx = vx;
	*_vy = vy;

}

double getDistance(_S_BULLET_OBJECT *pBullet,_S_Plane *pPlane )
{
	double bullet_pos_x = pBullet->m_fXpos;
	double bullet_pos_y = pBullet->m_fYpos;

	double target_pos_x = pPlane->m_fXpos;
	double target_pos_y = pPlane->m_fYpos;

	double vx = target_pos_x - bullet_pos_x;
	double vy = target_pos_y - bullet_pos_y;
	double dist = sqrt(vx*vx + vy*vy);
	
	return dist;
}

int main()
{

	for(int i=0;i<4;i++)
	{
		map_init(&gScreenBuf[i]);
		map_new(&gScreenBuf[i],35,48);
	}

	map_init(&gPlayerModel);
	map_load(&gPlayerModel,"plane1.dat");
	
	map_init(&gBulletModel);
	map_init(&gBulletModel2);
	map_load(&gBulletModel2,"plasma.dat");
	map_load(&gBulletModel,"plasma.dat");

	map_init(&gAlienModel);
	map_load(&gAlienModel,"alien.dat");

	double TablePosition[] = {0,6.0,12,18,24};
	//double TablePosition2[] = {0,6.0,12,18,24};
	
	for(int i=0;i<32;i++) {
		_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
		bullet_init(pObj,0,0,0,&gBulletModel);
	}
	for(int i=0;i<32;i++) {
		_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
		bullet_init(pObj,0,0,0,&gBulletModel2);
	}


	for(int i=0;i<4;i++)
	{
		_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
		alien_init(pObj,&gAlienModel);
		pObj->m_fXpos = TablePosition[i];
		pObj->m_fYpos = 2;
	
		//pObj->m_fXpos = TablePosition2[i];
		//pObj->m_fYpos = 7;
		
		pObj->m_nFSM = 1;
	}
	Plane_init(&gPlayerObject,&gPlayerModel,17,40);
	
	gPlayerObject.m_nFSM = 1;	
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
				for(int i =0;i<32;i++) {
					_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
					//double vx,vy;
					//pObj->m_fXpos=0;
					//pObj->m_fYpos=0;

					//getDirection(pObj,&gAlienObjects[i],&vx,&vy);
					//pObj->m_fvx=0;
					//pObj->pfFire(pObj,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,-1,-1,10.0,10.0);
					pObj->m_nFSM =1;
				}
			}
			if(acc_tick += delta_tick > 0.5) {
				//for(int i=0;i<32;i++) {
				//gBulletObjects2->pfFire(&gBulletObjects2[i],gAlienObjects[i].m_fXpos,
				//gAlienObjects->m_fYpos,1,1,10.0,10.0);
				gBulletObjects2->m_nFSM = 1;
				for(int i =0;i<32;i++) {
					_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
					pObj->pfApply(pObj,delta_tick);
				}
			}	

			gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
		for(int i=0;i<4;i++ ) 
		{
			_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
			pObj->pfApply(pObj,delta_tick);
			//double dist = getDistance(&gBulletObjects2,&pObj);

			//if(dist < 

		}
		for(int i =0;i<32;i++) {
			_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
			pObj->pfApply(pObj,delta_tick);
			if(pObj->m_nFSM != 0) {

				double dist = getDistance(pObj,&gPlayerObject);	
				
				if(dist < 1.0) {
					//pObj->m_nFSM = 0;
					for(int i=0;i<8;i++) {
						_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
						//pObj->m_nFSM = 0;
						//gPlayerObject.m_nFSM = 0;
					}
				}
				
			}

		}
	}

		//타이밍 계산 
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			gotoxy(0,0);
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
			
			gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);
			for(int i =0;i<32;i++) {
				_S_BULLET_OBJECT *pObj = &gBulletObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}
			for(int i =0;i<32;i++) {
				_S_BULLET_OBJECT *pObj = &gBulletObjects2[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}

			for(int i=0;i<4;i++ ) 
			{
				_S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
				pObj->pfDraw(pObj,&gScreenBuf[1]);
			}
			
			map_dump(&gScreenBuf[1],Default_Tilepalette);
			acc_tick = 0;
		}

	}

	return 0;

}
