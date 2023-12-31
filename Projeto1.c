//Daniel Scanavini Rossi RA:22000787, Lucas Valerio Berti RA:22007440, Leonardo Caberlim de Souza RA:22017958
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "FILA.h"

void menu()
{
    printf("=========SISTEMA DE GERENCIAMENTO DE TAREFAS=========\n");
    printf("\t1 - Adicionar uma nova tarefa\n");
    printf("\t2 - Modificar uma tarefa\n");
    printf("\t3 - Concluir uma tarefa\n");
    printf("\t4 - Alterar status da tarefa\n");
    printf("\t5 - Lista de tarefas pendentes\n");
    printf("\t6 - Lista de tarefas concluidas\n");
    printf("\t7 - Lista de tarefas concluidas(Com e sem atrasos)\n");
    printf("\t8 - Sair do programa\n");
    printf("\t>>");
}

void AddTask(Fila *f) 
{
    int flag = 0;
    tarefa j;
    system("cls");
    printf("Insira o codigo da tarefa: \n");
    scanf("%d", &j.codigo);
    printf("Digite o nome da tarefa: \n");
    fflush(stdin);
    scanf("%s", j.nome);
    printf("Insira o nome do projeto: \n");
    fflush(stdin);
    scanf("%s", j.projeto);
    printf("Insira o dia de inicio: \n");
    scanf("%d", &j.inicio.dia);
    printf("Insira o mes de inicio: \n");
    scanf("%d", &j.inicio.mes);
    printf("Insira o ano de inicio: \n");
    scanf("%d", &j.inicio.ano);
    printf("Insira o dia de limite: \n");
    scanf("%d", &j.fim.dia);
    printf("Insira o mes de limite: \n");
    scanf("%d", &j.fim.mes);
    printf("Insira o ano de limite: \n");
    scanf("%d", &j.fim.ano);
    j.status = 0; //1:atrasada, 0:em dia, -1:pendente
    InsereFila(f, j.codigo, j.nome, j.projeto, j.inicio, j.fim, j.status);
    printf("Tarefa inserida com sucesso! Aperte enter para continuar");
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
        printf("Tarefa com o codigo %d nao encontrada! Aperte enter para continuar",code);
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
        printf("\t>>");
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
                printf("Digite o novo dia de inicio: ");
                scanf("%d", &q->info.inicio.dia);
                printf("Digite o novo mes de inicio: ");
                scanf("%d", &q->info.inicio.mes);
                printf("Digite o novo ano de inicio: ");
                scanf("%d", &q->info.inicio.ano);
                break;
            case 5:
                printf("Digite o novo dia de limite: ");
                scanf("%d", &q->info.fim.dia);
                printf("Digite o novo mes de limite: ");
                scanf("%d", &q->info.fim.mes);
                printf("Digite o novo ano de limite: ");
                scanf("%d", &q->info.fim.ano);
                break;
            default:
                printf("Selecao invalida.\n");
        }
        printf("Deseja alterar mais algum dado? (s/n)");
        fflush(stdin);
        scanf("%c",&c);
        printf("Tarefa alterada com sucesso! Aperte enter para continuar");
    }while(c == tolower('s'));
}

Lista *CompleteTask(Fila *f, Lista *concluidas) 
{   
    time_t agora;
    struct tm *atual;
    int code;
    tarefa aux;
    Fila *aux2 = NULL;
    int flag=0;
    aux2 = CriaFila();

    printf("Insira o codigo da tarefa que deseja concluir: ");
    scanf("%d", &code);

    while (!VaziaFila(f))
    {
        aux = RetiraFila(f);
        if (aux.codigo != code)
        {
            InsereFila(aux2,aux.codigo, aux.nome, aux.projeto, aux.inicio, aux.fim, aux.status);
        }
        else
        {   
            flag =1;
            time(&agora);
            atual = localtime(&agora);
            aux.fim.dia = atual->tm_mday;
            aux.fim.mes = atual->tm_mon + 1;
            aux.fim.ano = atual->tm_year + 1900;
            concluidas = InsereLista(concluidas,aux);
            printf("Tarefa com o codigo %d concluida com sucesso! Aperte enter para continuar",code);
        }    
    }
    f->ini = aux2->ini;
    f->fim = aux2->fim;

    if (flag == 0)
    {
        printf("Tarefa com o codigo %d nao encontrada! Aperte enter para continuar\n",code);
        return concluidas;
    }
    return concluidas;
}

void TaskStatus(Fila *f, Lista **pendentes)
{
    int code,find=0,flag = 0;
    tarefa aux;
    Fila *aux2 = NULL;
    aux2 = CriaFila();
    Lista *novo = *pendentes;
    Lista *temp = NULL, *temp2 = NULL;

    printf("Insira o codigo da tarefa que deseja alterar o status: ");
    scanf("%d", &code);

    // Procurar na fila de tarefas
    while (!VaziaFila(f))
    {
        aux = RetiraFila(f);
        if (aux.codigo != code)
        {
            InsereFila(aux2,aux.codigo, aux.nome, aux.projeto, aux.inicio, aux.fim, aux.status);
        }
        else
        {
            find = 1;
            flag = 1;
            aux.status = -1;
            if (novo == NULL)
            {
                *pendentes = InsereLista(*pendentes,aux);
                printf("Tarefa com codigo %d esta pendente e foi movida para a lista de tarefas pendentes! Aperte enter para continuar\n", code);
            }
            else
            {
                while(novo != NULL && (aux.fim.ano > novo->info.fim.ano || (aux.fim.ano <= novo->info.fim.ano && aux.fim.mes > novo->info.fim.mes ||
                    (aux.fim.ano <= novo->info.fim.ano && aux.fim.mes <= novo->info.fim.mes && aux.fim.dia > novo->info.fim.dia))))
                {
                    temp = InsereLista(temp,novo->info);
                    novo = novo->prox;
                }
                if (novo == NULL)
                {
                    temp = InsereLista(temp,aux);
                    *pendentes = InverteLista(temp);
                    printf("Tarefa com codigo %d esta pendente e foi movida para a lista de tarefas pendentes! Aperte enter para continuar\n", code);
                }
                else
                {
                    novo = InverteLista(novo);
                    *pendentes = NULL;
                    while (novo != NULL)
                    {
                        *pendentes=InsereLista(*pendentes,novo->info);
                        novo = novo->prox;
                    }
                    *pendentes = InsereLista(*pendentes,aux);
                    while(temp != NULL)
                    {
                        *pendentes = InsereLista(*pendentes,temp->info);
                        temp = temp->prox;
                    }
                    printf("Tarefa com codigo %d esta pendente e foi movida para a lista de tarefas pendentes! Aperte enter para continuar\n", code);
                }
            }
        }
    }
    f->ini = aux2->ini;
    f->fim = aux2->fim;

    if (find == 0)
    {
        while (novo != NULL && novo->info.codigo != code) 
        {
            temp = novo;
            novo = novo->prox;
        }

        if (novo != NULL && novo->info.codigo == code) 
        {
            if (temp != NULL) 
            {
                temp->prox = novo->prox;
            } 
            else 
            {
                *pendentes = novo->prox;
            }

            flag = 1;
            novo->info.status = 0;
            InsereFila(f, novo->info.codigo, novo->info.nome, novo->info.projeto, novo->info.inicio, novo->info.fim, novo->info.status);
            free(novo); 
            printf("Tarefa com o codigo %d nao esta pendente e foi movida para a fila de tarefas! Aperte enter para continuar", code);
        } 
    }

    if (flag == 0)
    {
        printf("Tarefa com o codigo %d nao encontrada! Aperte enter para continuar",code);
        return;
    }
    return;
}

void Status(Lista *L)
{
    Lista *aux = L;
    while (aux != NULL)
    {
        if (aux->info.status == 1)
        {
            printf("Tarefas concluidas atrasadas: \n");
            printf(" Codigo: %d\n Nome: %s\n Projeto: %s\n Inicio: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
               aux->info.codigo, aux->info.nome, aux->info.projeto,
               aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano,
               aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano,
               aux->info.status);
        }
        else
        {
            printf("Tarefas concluidas em dia: \n");
            printf(" Codigo: %d\n Nome: %s\n Projeto: %s\n Inicio: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
               aux->info.codigo, aux->info.nome, aux->info.projeto,
               aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano,
               aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano,
               aux->info.status);
        }
        aux = aux->prox;
    }
}

void DueOrLate(Fila *trf) 
{
    time_t agora;
    struct tm *atual;
    time(&agora);
    atual = localtime(&agora);
    No *q = trf->ini;

    while (q != NULL) 
    {
        if (atual->tm_year + 1900 > q->info.fim.ano ||(atual->tm_year + 1900 == q->info.fim.ano && (atual->tm_mon + 1) > q->info.fim.mes) || (atual->tm_year + 1900 == q->info.fim.ano && (atual->tm_mon + 1) == q->info.fim.mes && atual->tm_mday > q->info.fim.dia)) 
        {
            q->info.status = 1;
        } 
        else 
        {
            q->info.status = 0;
        }
        q = q->prox;
    }
}

int main()
{
    Lista *concluidas,*pendentes;
    int select;
    Fila *trf;
    trf = CriaFila(trf);
    concluidas = CriaLista();
    pendentes = CriaLista();

    do{
        system("cls");
        DueOrLate(trf);
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
            case 3:
                concluidas = CompleteTask(trf,concluidas);
                break;
            case 4:
                TaskStatus(trf,&pendentes);
                break;
            case 5:
                printf("tarefas pendentes: \n");
                ImprimeLista(pendentes);
                printf("aperte enter para continuar");
                break;
            case 6:
                printf("tarefas concluidas: \n");
                ImprimeLista(concluidas);
                printf("aperte enter para continuar");
                break;
            case 7:
                Status(concluidas);
                break;
            case 8:
                printf("\t Programa finalizado com sucesso, aperte enter para finalizar \n");
                break;
            default:
                printf("\t Selecao invalida");
                break;
        }
        fflush(stdin);
        getchar();
    }while(select != 8);
    return 0;
}