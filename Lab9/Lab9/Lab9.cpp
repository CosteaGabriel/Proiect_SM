// Lab9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int stack_ovr(){
	int a = 1;

	if (a == 1){
		stack_ovr();
	}
	else return 0;
}

void vector_compare(){
	int vect1[10], vect2[10];

	printf("Compared adress od vectors id: %p\n", &vect1 - &vect2);

	for (int i = 0; i < 10; i++){
		printf("Compared adress for index %d is: %p\n", i, &vect1[i] - &vect2[i]);
	}
}

int stack_grow(){
	int a = 0, b = 9;
	return &a - &b;
}

int func(int a, int b){
	printf("adress of var a is: %p and adress of var b is: %p\n", &a, &b);

	printf("a = %d and b = %d\n", a, b);
	return a + b;
}
int _tmain(int argc, _TCHAR* argv[])
{	
	
	if (stack_grow() > 0)
	{
		printf("down\n");
	}
	else printf("up\n");
	
	func(5, 6);
	printf("adress of function func is: %p\n", &func);
	
	vector_compare();

	stack_ovr();
	return 0;
}

