//Daniel Scanavini Rossi RA:22000787, Lucas Valério Berti RA:22007440, Leonardo Caberlim de Souza RA:22017958
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
    printf("Tarefa inserida com sucesso!! Aperte enter para continuar");
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
        printf("Tarefa alterada com sucesso!! aperte enter para continuar");
    }while(c == tolower('s'));
}

void CompleteTask(Fila *f, Lista **concluidas) 
{   
    time_t agora;
    struct tm *atual;
    int code;
    No *q = f->ini;
    No *anterior = NULL;
    tarefa lixo;

    printf("Insira o codigo da tarefa que deseja concluir: ");
    scanf("%d", &code);

    while (q != NULL) 
    {
        if (q->info.codigo == code) 
        {
            time(&agora);
            atual = localtime(&agora);
            q->info.fim.dia = atual->tm_mday;
            q->info.fim.mes = atual->tm_mon + 1;
            q->info.fim.ano = atual->tm_year + 1900;
            
            if (anterior != NULL) 
            {
                anterior->prox = q->prox;
            } 
            else 
            {
                f->ini = q->prox;
            }
            
            q->prox = NULL;
            (*concluidas) = InsereLista(*concluidas, q->info);
            free(q);
            q = (anterior != NULL) ? anterior->prox : f->ini;
        } 
        else 
        {
            anterior = q;
            q = q->prox;
        }
    }

    printf("Tarefa concluida com sucesso!! Pressione enter para continuar");
}

void TaskStatus(Fila *f, Lista **pendentes)
{
    int code;
    printf("Insira o codigo da tarefa: ");
    scanf("%d", &code);

    No *q = f->ini;
    No *anterior = NULL;

    while (q != NULL)
    {
        if (q->info.codigo == code)
        {
            if (q->info.status == 0)
            {
                q->info.status = -1;

                if (anterior != NULL)
                {
                    anterior->prox = q->prox;
                }
                else
                {
                    f->ini = q->prox;
                }

                q->prox = NULL;

                Lista *novo = *pendentes;
                Lista *anteriorPendentes = NULL;

                while (novo != NULL && (q->info.fim.ano > novo->info.fim.ano ||
                                        (q->info.fim.ano == novo->info.fim.ano &&
                                         (q->info.fim.mes > novo->info.fim.mes ||
                                          (q->info.fim.mes == novo->info.fim.mes &&
                                           q->info.fim.dia > novo->info.fim.dia)))))
                {
                    anteriorPendentes = novo;
                    novo = novo->prox;
                }

                if (anteriorPendentes != NULL)
                {
                    anteriorPendentes->prox = InsereLista(anteriorPendentes->prox, q->info);
                }
                else
                {
                    *pendentes = InsereLista(*pendentes, q->info);
                }

                free(q);

                printf("Tarefa com codigo %d agora esta marcada como pendente e foi movida para a lista de tarefas pendentes\n", code);
                return;
            }
            else if (q->info.status == -1)
            {
                q->info.status = 0;

                if (anterior != NULL)
                {
                    anterior->prox = q->prox;
                }
                else
                {
                    f->ini = q->prox;
                }

                q->prox = NULL;

                if (f->ini == NULL)
                {
                    f->ini = q;
                }
                else
                {
                    f->fim->prox = q;
                }
                f->fim = q;

                printf("Tarefa com codigo %d nao esta mais pendente e foi movida para a fila de tarefas\n", code);
                return;
            }
        }
        else
        {
            anterior = q;
            q = q->prox;
        }
    }

    printf("Tarefa com codigo %d nao encontrada.\n", code);
}

void PrintPending(Lista *l)
{   
    Lista *aux = l;
    printf("Tarefas pendentes:\n");
    while(aux!=NULL)
    {
        printf(" Codigo: %d\n Nome: %s\n Projeto: %s\n Inicio: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
               aux->info.codigo, aux->info.nome, aux->info.projeto,
               aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano,
               aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano,
               aux->info.status);
        aux = aux->prox;
    }
    printf("Aperte enter para continuar");
}

void PrintCompleted(Lista *l)
{   
    Lista *aux = l;
    printf("Tarefas concluídas:\n");
    while (aux != NULL)
    {
        printf(" Código: %d\n Nome: %s\n Projeto: %s\n Início: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
               aux->info.codigo, aux->info.nome, aux->info.projeto,
               aux->info.inicio.dia, aux->info.inicio.mes, aux->info.inicio.ano,
               aux->info.fim.dia, aux->info.fim.mes, aux->info.fim.ano,
               aux->info.status);
        aux = aux->prox;
    }
    printf("Aperte enter para continuar");
}

void Status(Fila *trf) {
    No *q = trf->ini;

    printf("Tarefas Atrasadas:\n");
    while (q != NULL) {
        if (q->info.status == 1) {
            printf(" Código: %d\n Nome: %s\n Projeto: %s\n Início: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
                   q->info.codigo, q->info.nome, q->info.projeto,
                   q->info.inicio.dia, q->info.inicio.mes, q->info.inicio.ano,
                   q->info.fim.dia, q->info.fim.mes, q->info.fim.ano,
                   q->info.status);
        }
        q = q->prox;
    }

    q = trf->ini;

    printf("Tarefas Sem Atrasos:\n");
    while (q != NULL) {
        if (q->info.status == 0) {
            printf(" Código: %d\n Nome: %s\n Projeto: %s\n Início: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
                   q->info.codigo, q->info.nome, q->info.projeto,
                   q->info.inicio.dia, q->info.inicio.mes, q->info.inicio.ano,
                   q->info.fim.dia, q->info.fim.mes, q->info.fim.ano,
                   q->info.status);
        }
        q = q->prox;
    }
}

void DueOrLate(Fila *trf) 
{
    time_t agora;
    struct tm *atual;
    time(&agora);
    atual = localtime(&agora);

    No *q = trf->ini;

    while (q != NULL) {
        if (atual->tm_year + 1900 > q->info.fim.ano ||(atual->tm_year + 1900 == q->info.fim.ano && (atual->tm_mon + 1) > q->info.fim.mes) || (atual->tm_year + 1900 == q->info.fim.ano && (atual->tm_mon + 1) == q->info.fim.mes && atual->tm_mday > q->info.fim.dia)) 
        {
            q->info.status = 1;
        } else 
        {
            q->info.status = 0;
        }
        q = q->prox;
    }
}

int main()
{
    setlocale(LC_ALL,"portuguese");
    Lista *concluidas,*pendentes;
    char continuo = 's';
    int select;
    Fila *trf;
    trf = CriaFila(trf);
    concluidas = CriaLista();
    pendentes = CriaLista();
    do{
        system("cls");
        DueOrLate;
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
                CompleteTask(trf,&concluidas);
                break;
            case 4:
                TaskStatus(trf,&pendentes);
                break;
            case 5:
                PrintPending(pendentes);
                break;
            case 6:
                PrintCompleted(concluidas);
                break;
            case 7:
                Status(trf);
                break;
            case 8:
                printf("\t Programa finalizado com sucesso, aperte enter para finalizar \n");\
                imprimeFila(trf);//LEMBRAR DE TIRAR DEPOIS
                break;
            default:
                printf("\t Selecao invalida");
                break;
        }
        fflush(stdin);
        getchar();
    }while(select != 8);

    fflush(stdin);
    getchar();
    return 0;
}