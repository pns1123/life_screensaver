#include <stdio.h>

char ESC=27;

void set_red() { printf("\033[1;31m"); }

void set_green() { printf("\033[1;32m"); }

void set_purple() { printf("\033[0;35m"); }

void set_bold() { printf("%c[1m",ESC); }

void reset_printf() { printf("\033[0m"); printf("%c[0m",ESC); }

bool bool_array_equal(bool arr1[], bool arr2[], unsigned int length){
	for(unsigned int i=0; i<length; ++i){
		if(arr1[i] != arr2[i]){
			return false;
		}
	}
	return true;
}
