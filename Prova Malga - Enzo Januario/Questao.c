#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	int quantDis, *ptr;
	float velocidade, *ptx;
	char status[20];
	char *pty;
	
	printf("Insira o caractere I: ");
	fflush(stdin);
	gets(status);
	
	quantDis = 3;
	velocidade = 1000;
	ptr = &quantDis;
	ptx = &velocidade;
	pty = &status;
	
	*ptr = *ptr + 5;
	*ptx = *ptx * 2;
	
	printf("Insira o caractere A: ");
	fflush(stdin);
	gets(pty);
	
	
	printf("Quatidade de disp: %d", quantDis);
	printf("\nVelocidade: %.2f: ", velocidade);
	printf("\nStatus: %s", status);
	
	
}