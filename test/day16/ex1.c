#include <stdio.h>

void Reverse(int *arr)
{
	int temp;
	for(int i =0;i<2;i++) {
		temp=arr[i];
		arr[i] = arr[4-i];		
		arr[4-i] = temp;
	}
}

// temp = a, a = b, b = temp
int main()
{
	int array_test[5]= {1,2,3,4,5};
	
	for(int i=0;i <5;i++) {
		printf("%d ",array_test[i]);
	}
	
	/*
	for(int i=0; i<2;i++) {
		int temp;
		temp = array_test[i];
		array_test[i] = array_test[4-i];
		array_test[4-i] = temp;
		printf("%d ",array_test[i]);
		//i =0,0 4 i=0/temp=1/arr0 = 5/arr4=temp 1
		//i =1,1 3 i=1/temp=2/arr1 = 4/arr3=temp 2
		//i =2,2 2 i=2/temp=3/arr2 = 3/arr2=temp 3
		//i =3,3 1 i=3/temp=4/arr3 = 4/arr1=temp 4
		//i =4,4 0 i=4/temp=5/arr4 = 5/arr0=temp 5
	}
	*/
	Reverse(array_test);

	puts("");
	for(int i=0;i <5;i++) {
		printf("%d ",array_test[i]);
	}

}
