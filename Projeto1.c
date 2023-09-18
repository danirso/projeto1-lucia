//Leonardo Caberlim de Souza RA:22017958 Daniel Scanavini Rossi RA: 22000787 Lucas Valério Berti RA: 22007440
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "FILA.h"

struct Data
{
    int dia;
    int mes;
    int ano;
}; typedef struct Data data;


struct Tarefa
{
    int codigo;
    char nome[30];
    char projeto[30];
    data inicio;
    data fim;
    int status;
}; typedef struct Tarefa tarefa;

void AddTask(){
    Fila *trfs;
    tarefa j;
    trfs = CriaFila();
    printf("Insira o codigo da tarefa: \n");
    scanf("%d",&j.codigo);
    printf("Digite o nome da tarefa: \n");
    fflush(stdin);
    scanf("%s",j.nome);
    printf("Insira o nome do Projeto: \n");
    fflush(stdin);
    scanf("%s",j.projeto);
    printf("Insira o dia de Início: \n");
    scanf("%d",&j.inicio.dia);
    printf("Insira o mes de Início: \n");
    scanf("%d",j.inicio.mes);
    printf("Insira o ano de Início: \n");
    scanf("%d",j.inicio.ano);
    printf("Insira o dia de Término: \n");
    scanf("%d",&j.fim.dia);
    printf("Insira o mes de Término: \n");
    scanf("%d",j.fim.mes);
    printf("Insira o ano de Término: \n");
    scanf("%d",j.fim.ano);
   

    InsereFila(trfs,j);






}


void menu(){

    printf("Sistema de Gerenciamento 5000\n");
    printf("\t1 - Adicionar uma nova tarefa\n");
    printf("\t2 - Modificar uma tarefa\n");
    printf("\t3 - Concluir uma tarefa\n");
    printf("\t4 - Alterar status da tarefa\n");
    printf("\t5 - Lista de tarefas pendentes\n");
    printf("\t6 - Lista de tarefas concluídas\n");
    printf("\t7 - Lista de tarefas concluídas(Com e sem atrasos)\n");
    printf("\t8 - Sair do programa");
}



int main(){
    setlocale(LC_ALL,"portuguese");
    system("clear");
    menu();
    char continuo = "s";
    int select;
    do{
    scanf("%d",&select);
    switch (select)
    {
    case 1:
        AddTask();
        break;
    
    default:
        break;
    }
    printf("\nDeseja realizar outra operação? (s/n)");
    fflush(stdin);
    scanf("%c",&continuo);
    }while(continuo == tolower("s"));
    return 0;

}