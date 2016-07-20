#include <stdio.h>
/*
void Reverse(int array[])
{
	
	for(int i =0;i<5;i++) {
		int array_list[i] = array[];		
		array_list[i] = array_list[4-i];
	}
}
*/
// temp = a, a = b, b = temp
int main()
{
	int array_test[5]= {1,2,3,4,5};
	
	for(int i=0;i <5;i++) {
		printf("%d ",array_test[i]);
	}
	puts("");
	for(int i=0; i<5;i++) {
		int temp;
		temp = array_test[i];
		array_test[i] = array_test[4-i];
		array_test[4-i] = temp;
		printf("%d ",array_test[i]);
		//i =0,0 4 
		//i =1,1 3
		//i =2,2 2
		//i =3,3 1
		//i =4,4 0
	}
	puts("");
	for(int i=0;i <5;i++) {
		printf("%d ",array_test[i]);
	}

}
