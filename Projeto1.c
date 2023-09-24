//Leonardo Caberlim de Souza RA:22017958, Daniel Scanavini Rossi RA: 22000787, Lucas Valério Berti RA: 22007440
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "FILA.h"

void menu()
{
    printf("Sistema de Gerenciamento 5000\n");
    printf("\t1 - Adicionar uma nova tarefa\n");
    printf("\t2 - Modificar uma tarefa\n");
    printf("\t3 - Concluir uma tarefa\n");
    printf("\t4 - Alterar status da tarefa\n");
    printf("\t5 - Lista de tarefas pendentes\n");
    printf("\t6 - Lista de tarefas concluídas\n");
    printf("\t7 - Lista de tarefas concluídas(Com e sem atrasos)\n");
    printf("\t8 - Sair do programa\n");
}

void AddTask(Fila *f) 
{
    tarefa j;
    system("cls");
    printf("Insira o codigo da tarefa: \n");
    scanf("%d", &j.codigo);
    printf("Digite o nome da tarefa: \n");
    fflush(stdin);
    scanf("%s", j.nome);
    printf("Insira o nome do Projeto: \n");
    fflush(stdin);
    scanf("%s", j.projeto);
    printf("Insira o dia de Início: \n");
    scanf("%d", &j.inicio.dia);
    printf("Insira o mes de Início: \n");
    scanf("%d", &j.inicio.mes);
    printf("Insira o ano de Início: \n");
    scanf("%d", &j.inicio.ano);
    printf("Insira o dia de limite: \n");
    scanf("%d", &j.fim.dia);
    printf("Insira o mes de limite: \n");
    scanf("%d", &j.fim.mes);
    printf("Insira o ano de limite: \n");
    scanf("%d", &j.fim.ano);
    j.status = 0;
    InsereFila(f, j.codigo, j.nome, j.projeto, j.inicio, j.fim, j.status);
}

void ChangeTask (Fila *f)
{
    No * q = f->ini;
    int code,select;
    char c='s';
    printf("Insira o codigo da tarefa que deseja alterar: ");
    scanf("%d",&code);
    while (q != NULL && q->info.codigo != code)
    {
        q=q->prox;
    }
    if(q == NULL)
    {
        printf("Tarefa com o codigo %d nao encontrada",code);
        return;
    }

    do
    {
        system("cls");
        printf("Qual informacao deseja alterar: \n");
        printf("\t1 - Alterar o codigo\n");
        printf("\t2 - Alterar o nome\n");
        printf("\t3 - Alterar o nome do projeto\n");
        printf("\t4 - Alterar a data de inicio\n");
        printf("\t5 - Alterar a data de limite\n");
        scanf("%d",&select);

        switch (select) {
            case 1:
                printf("Digite o novo codigo: ");
                scanf("%d", &q->info.codigo);
                break;
            case 2:
                printf("Digite o novo nome: ");
                scanf("%s", q->info.nome);
                break;
            case 3:
                printf("Digite o novo nome do projeto: ");
                scanf("%s", q->info.projeto);
                break;
            case 4:
                printf("Digite a nova dia de inicio: ");
                scanf("%d", &q->info.inicio.dia);
                printf("Digite a nova mes de inicio: ");
                scanf("%d", &q->info.inicio.mes);
                printf("Digite a nova ano de inicio: ");
                scanf("%d", &q->info.inicio.ano);
                break;
            case 5:
                printf("Digite a nova dia de limite: ");
                scanf("%d", &q->info.fim.dia);
                printf("Digite a nova mes de limite: ");
                scanf("%d", &q->info.fim.mes);
                printf("Digite a nova ano de limite: ");
                scanf("%d", &q->info.fim.ano);
                break;
            default:
                printf("Selecao invalida.\n");
        }
        printf("Deseja alterar mais algum dado? (s/n)");
        fflush(stdin);
        scanf("%c",&c);
    }while(c == tolower('s'));
}




int main()
{
    setlocale(LC_ALL,"portuguese");
    char continuo = 's';
    int select;
    Fila *trf;
    trf = CriaFila(trf);
    do{
        system("cls");
        menu();
        scanf("%d",&select);
        switch (select)
        {
            case 1:
              AddTask(trf);
                break;
            case 2: 
                ChangeTask(trf);
                break;
            default:
                printf("Selecao invalida");
                break;
        }
        printf("\nDeseja realizar outra operacao? (s/n)");
        fflush(stdin);
        scanf("%c",&continuo);
    }while(continuo == tolower('s'));
    imprimeFila(trf);
    scanf("%d",&select);
    return 0;
}