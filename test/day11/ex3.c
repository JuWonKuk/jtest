#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int main()
{
	char title_palette[] = {'.','#','@'};
	_S_MAP_OBJECT carObj;
	map_init(&carObj);
	map_load(&carObj,"car.dat");		
	map_dump(&carObj,title_palette);
	return 0;
}
