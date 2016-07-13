#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../../cstudy2016/engine/engine2d.h"
#include "../mapEditor/map.h"

struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuffer;

int main()
{
	set_conio_terminal_mode();
	acc_tick = last_tick = 0;
	
	map_init(&gScreenBuffer);
	map_new(&gScreenBuffer,17,16);

	while(bLoop) {
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
		}
		//타이밍 계산
		acc_tick += delta_tick;
		if(acc_tick > 1.0) {
			gotoxy(0,0);
			map_dump(&gScreenBuffer,Default_Tilepalette);
			//puts("tick...\r");
			acc_tick = 0;
		}

	}

	return 0;
}
