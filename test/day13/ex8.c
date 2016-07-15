#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>

#include "../../cstudy2016/engine/engine2d.h"
#include "../mapEditor/map.h"
#include "plane.h"
#include "bullet.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuf[4];

_S_MAP_OBJECT gPlayer;
_S_MAP_OBJECT gPotab;
_S_MAP_OBJECT gBulletModel;
//_S_MAP_OBJECT gBulletModel2;

_S_Plane gPlayerObject;
_S_Plane gPotabObject;
S_BULLET_OBJECT gBulletObject;
//S_BULLET_OBJECT gBulletObject2;
int main()
{

	for(int i=0;i<4;i++) {
		map_init(&gScreenBuf[i]);
		//map_new(&gScreenBuf[i],35,16);
		gScreenBuf[i].fpNew(&gScreenBuf[i],50,30);
		
	}
	
	map_init(&gBulletModel);
	map_init(&gPlayer);
	map_init(&gPotab);

	gBulletModel.fpLoad(&gBulletModel,"plasma.dat"); 
	//gBulletModel2.fpLoad(&gBulletModel2,"plasma.dat"); 
	gPlayer.fpLoad(&gPlayer,"plane1.dat");
	gPotab.fpLoad(&gPotab,"potab.dat");

	Plane_init(&gPlayerObject,&gPlayer,25,25);
	Plane_init(&gPotabObject,&gPotab,0,0);
	bullet_init(&gBulletObject,0,0,0,&gBulletModel);
	//bullet_init(&gBulletObject2,0,0,0,&gBulletModel2);

	set_conio_terminal_mode();
	acc_tick = last_tick = 0;
	
	system("clear");

	int targetx, targety;
	int targetx2, targety2;

	int fire_x, fire_y;

	int fire_x2, fire_y2;
	while(bLoop) {
		//비행기
		targetx = gPotabObject.m_nXpos;
		targety = gPotabObject.m_nYpos;
		fire_x = gPlayerObject.m_nXpos;
		fire_y = gPlayerObject.m_nYpos;
		//포탑

		//double vx2, vy2, c2;
		//vx2 = targetx2 - fire_x2;
		//vy2 = targety2 - fire_y2;
		//c2 = sqrt(vx2*vx2 + vy2*vy2);
		//vx2 /=c2; vy2 /= c2;

		//targetx2 = gPlayerObject.m_nXpos;
		//targety2 = gPlayerObject.m_nYpos;
		//fire_x2 = gPotabObject.m_nXpos;
		//fire_y2 = gPotabObject.m_nYpos;


		//타이밍 처리
		clock_gettime(CLOCK_MONOTONIC, &work_timer);
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
				double vx, vy, c;
				vx = targetx - fire_x;
				vy = targety - fire_y;
				c = sqrt(vx*vx + vy*vy);
				vx /=c; vy /= c;

				bullet_fire(&gBulletObject,fire_x,fire_y,vx,vy,10.0,10.0);

			//bullet_fire(&gBulletObject2,fire_x2,fire_y2,vx2,vy2,10.0,10.0);
			}
			gPlayerObject.fpApply(&gPlayerObject,delta_tick,ch);
			//Plane_Apply(&gPlayerObject,delta_tick,ch);
			//gPotabObject.fpApply(&gPotabObject,delta_tick);
		}
		 	//bullet_apply(&gBulletObject2,delta_tick);
		bullet_apply(&gBulletObject,delta_tick);
		//타이밍 계산
		acc_tick += delta_tick;
		if(acc_tick > 0.1) {
			//puts("tick...\r");
			map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);

			bullet_draw(&gBulletObject,&gScreenBuf[1]);
			//bullet_draw(&gBulletObject2,&gScreenBuf[1]);

			gotoxy(0,0);

			gPotabObject.fpDraw(&gPotabObject,&gScreenBuf[1]); 
			gPlayerObject.fpDraw(&gPlayerObject,&gScreenBuf[1]);
			//Plane_Draw(&gPlayerObject,&gScreenBuf[1]);

			map_dump(&gScreenBuf[1],Default_Tilepalette);
			acc_tick = 0;
		}

	}

	return 0;
}
