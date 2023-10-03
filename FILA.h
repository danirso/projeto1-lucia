#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data
{
    int dia;
    int mes;
    int ano;

} data;

typedef struct Tarefa
{
    int codigo;
    char nome[30];
    char projeto[30];
    data inicio;
    data fim;
    int status;
} tarefa;

typedef struct Node
{
    tarefa info;
    struct Node *prox;
} Lista;


typedef struct nos
{
    tarefa info;
    struct nos *prox;
} No;

typedef struct fila
{
    No *ini;
    No *fim;
} Fila;

Lista *CriaLista()
{
    return NULL;
}

Lista *InsereLista(Lista *recebida, tarefa t)
{
    Lista *novo;
    novo = malloc(sizeof(Lista));
    novo->info = t;
    novo->prox = recebida;
    return novo;
}

int VaziaFila(Fila *f)
{
    if (f->ini == NULL)
        return 1;
    return 0;
}

Fila *CriaFila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim(No* fim, tarefa A)
{
    No* p = (No*) malloc(sizeof(No));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) 
        fim->prox = p;
    return p;
}

void InsereFila(Fila *f, int codigo, const char* nome, const char* projeto, data inicio, data fim, int status)
{
    tarefa trf;
    trf.codigo = codigo;
    strncpy(trf.nome, nome, sizeof(trf.nome));
    strncpy(trf.projeto, projeto, sizeof(trf.projeto));
    trf.inicio = inicio;
    trf.fim = fim;
    trf.status = status;

    f->fim = ins_fim(f->fim, trf);
    if (f->ini == NULL) 
    {
        f->ini = f->fim;
    }
}
No *retira_ini(No *ini)
{
    
    No* p = ini->prox;
    free(ini);
    return p;
}

tarefa RetiraFila(Fila* f)
{
    tarefa trf;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); 
    }
    
    trf = f->ini->info;
    f->ini = retira_ini(f->ini);
    
    if (VaziaFila(f)) 
    {
        f->fim = NULL;
    }
    
    return trf;
}

void imprimeFila(Fila *f)
{
    No *q;
    for (q = f->ini; q != NULL; q = q->prox)
    {
        printf(" Codigo: %d\n Nome: %s\n Projeto: %s\n Inicio: %02d/%02d/%04d\n Fim: %02d/%02d/%04d\n Status: %d\n\n",
               q->info.codigo, q->info.nome, q->info.projeto,
               q->info.inicio.dia, q->info.inicio.mes, q->info.inicio.ano,
               q->info.fim.dia, q->info.fim.mes, q->info.fim.ano,
               q->info.status);
    }
    printf("\n");
}

Fila *liberaFila(Fila *f)
{
    No *q = f->ini;
    while (q != NULL)
    {
        No *t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

#endif