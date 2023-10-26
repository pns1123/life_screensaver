#include <stdio.h>
#include <stdlib.h>

//https://www.geeksforgeeks.org/scanf-and-fscanf-in-c/

int main(void) {
	FILE *fp = fopen("pattern.rle", "r");
	if(fp == NULL){
		perror("Unable to open file!");
		exit(1);
	}
	char chunk[128];

	while(fgets(chunk, sizeof(chunk), fp) != NULL){
		fputs(chunk, stdout);
		fputs("|*\n", stdout); // indicator of end of chunk
	}

}
