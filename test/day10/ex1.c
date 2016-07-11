#include <stdio.h>

void draw_tri1()
{
	int ix,iy;
	//for(iy = 0; iy < 10; iy++) {
	//	for(ix = 10; ix > iy; ix--) {
	//		putchar('*');
	//	}
	//	puts("");
	//}
	
	for(iy=0; iy <10;iy++) {
		for(ix = 10; ix > 0;ix--) 
			printf(" ");
			
		puts("");
	}
}

int main()
{
	draw_tri1();
	

	return 0;
}
