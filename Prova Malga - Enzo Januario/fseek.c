#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

struct cadastro{
 char nome[20], rua[20];
 int idade;
 };
 
int main(){
FILE *ex = fopen("arquivo.txt","wb");


struct cadastro busca,cad[4] ={"Ricardo","Rua 1",31, 
							 "Carlos","Rua 2",28, 
							 "Ana","Rua 3",45,
							 "Bianca","Rua 4",32};

	fwrite(cad,sizeof(struct cadastro),4,ex);
	
	fclose(ex);
	
	ex = fopen("arquivo.txt","rb");

fseek(ex,1*sizeof(struct cadastro),SEEK_SET);

fread(&busca,sizeof(struct cadastro),1, ex);
printf("%s\n%s\n%d\n",busca.nome,busca.rua,busca.idade);

fclose(ex);
system("pause");
return 0;
}