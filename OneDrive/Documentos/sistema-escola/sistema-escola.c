#include<stdio.h>
#include<conio.h>

void addestudante();
void dadoestudante();
void pesquisarestudante();
void apagar();

struct estudante{
	char primeiro_nome[20];
	char ultimo_nome[20];
	int numero;
	char Turma[10];
	char cidade[20];
	float ira;
};

void main(){
	int escolha;
	while(escolha!= 5){
		printf("\t\t\t=======SISTEMA DE GERENCIAMENTO DE ESCOLA========");
		printf("\n\n\n\t\t\t\t  1. Adicionar dado de estudante\n");
		printf("\t\t\t\t  2. Ver dados de estudantes\n");
		printf("\t\t\t\t  3. Pesquisar estudante\n");
		printf("\t\t\t\t  4. Apagar estudante\n");
		printf("\t\t\t\t  5. Sair\n");
		printf("\t\t\t\t  _______________________________\n");
		printf("\t\t\t\t ");
		scanf("%d", &escolha);
		
		switch(escolha){
		case 1:
			system("cls");
			addestudante();
			system("cls");
			break;
		
		case 2:
            system("cls");
			dadoestudante();
			printf("\t\t\t\tPressione qualquer tecla para sair\n");
			getch();
			system("cls");
			break;
		
		case 3:
			system("cls");
			pesquisarestudante();
			printf("\t\t\t\tPressione qualquer tecla para sair\n");
			getch();
			system("cls");
			break;	
		
		case 4:
			system("cls");
			apagar();
			printf("\t\t\t\tPressione qualquer tecla para sair\n");
			getch();
			system("cls");
			break;
		}
		
  	  }	
}

void addestudante(){
	char outro;
	FILE *fp;
	struct estudante info;
	
	do{
        system("cls");
		printf("\t\t\t\t ========Adicionar Informacoes do Estudante======\n\n\n");
		fp=fopen("info_estudante.txt", "a");
		printf("\n\t\t\t Digite o Primeiro Nome : ");
		scanf("%s", &info.primeiro_nome);
		printf("\n\t\t\t Digite o Ultimo Nome   : ");
		scanf("%s", &info.ultimo_nome);
		printf("\n\t\t\t Digite o Numero        : ");
		scanf("%d", &info.numero);
		printf("\n\t\t\t Digite a Turma         : ");
		scanf("%s", &info.Turma);
		printf("\n\t\t\t Digite a Cidade        : ");
		scanf("%s", &info.cidade);
		printf("\n\t\t\t Digite o IRA           : ");
		scanf("%f", &info.ira);
		printf("\n\t\t\t_____________________________\n");
		
		if(fp==NULL){
			fprintf(stderr,"\t\t\t Nao e possivel abrir o arquivo\n");
		}else{
			printf("\t\t\t Dados armazenados com sucesso\n");
		}
		
		fwrite(&info,sizeof(struct estudante), 1,fp);
		fclose(fp);
		
		printf("\t\t\t Voce quer adicionar outro dado?(s/n) :");
		fflush(stdin);
		scanf("%s",&outro);
		
	}while(outro == 's' || outro == 'S');
}

void dadoestudante(){
	FILE *fp;
	struct estudante info;
	fp=fopen("info_estudante.txt", "r");
	printf("\t\t\t\t ========Dados Estudantes======\n\n\n");
	
    if(fp==NULL){
        fprintf(stderr,"\t\t\t\tNao e possivel abrir o arquivo\n");
    }else{
        printf("\t\t\t\tDados\n");
        printf("\t\t\t\t_______\n\n");
    }
    
    while(fread(&info,sizeof(struct estudante),1,fp)){
		printf("\n\t\t\t\tNome do Estudante: %s %s",info.primeiro_nome,info.ultimo_nome);
		printf("\n\t\t\t\tNumero           : %d",info.numero);
		printf("\n\t\t\t\tTurma            : %s",info.Turma);
		printf("\n\t\t\t\tCidade           : %s",info.cidade);
		printf("\n\t\t\t\tIRA              : %f",info.ira);
		printf("\n\t\t\t\t______________________________________________\n");
	}
	fclose(fp);
	getch();
}

void pesquisarestudante(){
	FILE *fp;
	struct estudante info;
	int numero, encontrado=0;
	
	fp=fopen("info_estudante.txt", "r");
	
	printf("\t\t\t\t ========Pesquisar Estudante======\n\n\n");
	printf("\t\t\t Digite o numero :");
	scanf("%d",&numero);
	
	while(fread(&info,sizeof(struct estudante),1,fp)){
		if(info.numero==numero){
        encontrado=1;
		printf("\n\t\t\t\tNome do Estudante: %s %s",info.primeiro_nome,info.ultimo_nome);
		printf("\n\t\t\t\tNumero           : %d",info.numero);
		printf("\n\t\t\t\tTurma            : %s",info.Turma);
		printf("\n\t\t\t\tCidade           : %s",info.cidade);
		printf("\n\t\t\t\tIRA              : %f",info.ira);
		printf("\n\t\t\t\t______________________________________________\n");
	}
	}
	
	if (!encontrado){
		printf("\n\t\t\tDado nao encontrado!\n");
	}
	
	fclose(fp);
	getch();
}

void apagar(){
	FILE *fp, *fp1;
	struct estudante info;
	int numero, encontrado=0;
	
	printf("\t\t\t\t ========Apagar Dado de Estudante======\n\n\n");
	fp=fopen("info_estudante.txt","r");
	fp1=fopen("temp.txt","w");
	printf("\t\t\tDigite o Numero: ");
	scanf("%d", &numero);
	
	if(fp==NULL || fp1 == NULL){
        fprintf(stderr,"\t\t\t\tNao e possivel abrir o arquivo\n");
    }
    while(fread(&info,sizeof(struct estudante),1,fp)){
		if(info.numero==numero){
        encontrado=1;
		}else{
			fwrite(&info,sizeof(struct estudante),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	
	if(encontrado){
		remove("info_estudante.txt");
		rename("temp.txt", "info_estudante.txt");
		printf("\n\t\t\tDado apagado com sucesso!\n");
	}
	if(!encontrado){
		printf("\n\t\t\tDado nao encontrado!");
	}
	
	getch();
}