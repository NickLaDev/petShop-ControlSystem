#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

// Estrutura para a data de nascimento
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura para as informações do Pet
typedef struct Pet {
    int id;                 // Código inteiro aleatório (100-999), não repetido
    char nome[51];          // Alfanumérico, máximo 50 caracteres
    char especie[31];       // Alfanumérico, máximo 30 caracteres
    int idade;              // Inteiro
    Data dataNascimento;    // Estrutura Data
    int prioridade;         // 0 para Emergência, 1 para Normal
} Pet;


typedef struct nos
{
    Pet info;
    struct nos *prox;
}Nos;

typedef struct fila
{
    Nos * ini;
    Nos * fim;
} Fila;

int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* ins_fim (Nos *fim, Pet p)
{
    Nos *n = (Nos*)malloc(sizeof(Nos));
    n->info = p;
    n->prox = NULL;
    if (fim != NULL) /* verifica se lista n�o estava vazia */
    fim->prox = n;
    return n;
}

void InsereFila (Fila* f, Pet p)
{
    f->fim = ins_fim(f->fim,p);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

Pet RetiraFila (Fila* f)
{
    Pet p;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    p = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return p;
}

/*void imprimeFila (Fila* f)
{
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info);
    }
    printf("\n");
}
*/

// Nova função de impressão para os relatórios
void imprimeRelatorioFila (Fila* f, const char* tipoFila)
{
    Nos* q;

    printf("\n--- Relatório da Fila de %s ---\n", tipoFila);
    if(VaziaFila(f)){
        printf("Nenhum pet na fila.\n");
        return;
    }

    printf("--------------------------------------------------------------------------------------------\n");
    printf("ID   | Nome do Pet          | Espécie              | Idade | Data Nasc.   | Prioridade\n");
    printf("--------------------------------------------------------------------------------------------\n");

    for (q = f->ini; q != NULL; q = q->prox)
    {
        // Acessamos cada campo da struct 'info'
        printf("%-4d | %-20s | %-20s | %-5d | %02d/%02d/%-8d | %s\n",
               q->info.id,
               q->info.nome,
               q->info.especie,
               q->info.idade,
               q->info.dataNascimento.dia,
               q->info.dataNascimento.mes,
               q->info.dataNascimento.ano,
               q->info.prioridade == 0 ? "Emergência" : "Normal");
    }
    printf("--------------------------------------------------------------------------------------------\n");
}

Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

#endif // FILA_H_INCLUDED
