#include <stdio.h>
#include <stdlib.h>
#include "FILA.h"
#include <locale.h>
#include <string.h>
#include <time.h>


void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void salvar_dados(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos) {
    FILE *arquivo = fopen("dados_clinica.txt", "w"); // "w" para escrever (write)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    Nos* q;

    // Salva a fila de Emergência
    // Usamos um 'E' para identificar que o pet pertence a esta fila
    q = filaEmergencia->ini;
    while (q != NULL) {
        fprintf(arquivo, "E;%d;%s;%s;%d;%d;%d;%d\n",
                q->info.id, q->info.nome, q->info.especie, q->info.idade,
                q->info.dataNascimento.dia, q->info.dataNascimento.mes, q->info.dataNascimento.ano);
        q = q->prox;
    }

    // Salva a fila Normal (identificador 'N')
    q = filaNormal->ini;
    while (q != NULL) {
        fprintf(arquivo, "N;%d;%s;%s;%d;%d;%d;%d\n",
                q->info.id, q->info.nome, q->info.especie, q->info.idade,
                q->info.dataNascimento.dia, q->info.dataNascimento.mes, q->info.dataNascimento.ano);
        q = q->prox;
    }

    // Salva a fila de Atendidos (identificador 'A')
    q = filaAtendidos->ini;
    while (q != NULL) {
        // Para os atendidos, a prioridade original já está no 'q->info.prioridade'
        fprintf(arquivo, "A;%d;%s;%s;%d;%d;%d;%d;%d\n",
                q->info.id, q->info.nome, q->info.especie, q->info.idade,
                q->info.dataNascimento.dia, q->info.dataNascimento.mes, q->info.dataNascimento.ano, q->info.prioridade);
        q = q->prox;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}


void carregar_dados(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos) {
    FILE *arquivo = fopen("dados_clinica.txt", "r"); // "r" para ler (read)
    if (arquivo == NULL) {
        printf("Arquivo de dados não encontrado. Iniciando um novo sistema.\n");
        return;
    }

    Pet tempPet;
    char tipoFila;

    // Lê os pets das filas de espera
    while (fscanf(arquivo, "%c;", &tipoFila) != EOF) {
        if (tipoFila == 'A') { // Se for da fila de atendidos, o formato é diferente
             fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%d;%d;%d\n",
                   &tempPet.id, tempPet.nome, tempPet.especie, &tempPet.idade,
                   &tempPet.dataNascimento.dia, &tempPet.dataNascimento.mes, &tempPet.dataNascimento.ano, &tempPet.prioridade);
            InsereFila(filaAtendidos, tempPet);
        } else {
             fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%d;%d\n",
                   &tempPet.id, tempPet.nome, tempPet.especie, &tempPet.idade,
                   &tempPet.dataNascimento.dia, &tempPet.dataNascimento.mes, &tempPet.dataNascimento.ano);

            if (tipoFila == 'E') {
                tempPet.prioridade = 0; // Emergência
                InsereFila(filaEmergencia, tempPet);
            } else if (tipoFila == 'N') {
                tempPet.prioridade = 1; // Normal
                InsereFila(filaNormal, tempPet);
            }
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

void adicionarPet(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos){
    Pet novoPet;
    srand(time(NULL));
    int min = 100, max = 999,confirmar=0;
    limparTela();

    while(confirmar==0){
        printf("--- Você está no menu de Adiconar um novo PET ---\n");
        printf("\nDigite o nome do PET: ");
        limpar_buffer();
        fgets(novoPet.nome, 51, stdin);
        novoPet.nome[strcspn(novoPet.nome, "\n")] = 0;
        //scanf("%s", novoPet.nome);
        printf("\nDigite a espécie do PET: ");
        scanf("%s", novoPet.especie);
        printf("\nDigite a idade do PET: ");
        scanf("%d", &novoPet.idade);
        printf("\nDigite a data de nascismento do PET (dd mm aaaa):");
        scanf("%d %d %d", &novoPet.dataNascimento.dia, &novoPet.dataNascimento.mes, &novoPet.dataNascimento.ano);
        do{
            printf("\nDigite a prioridade do PET (0 para Emergência, 1 para Normal): ");
            scanf("%d", &novoPet.prioridade);
            if(novoPet.prioridade != 0 && novoPet.prioridade != 1){
                printf("\nPrioridade inválida! Tente novamente. \n");
        }
        }while(novoPet.prioridade != 0 && novoPet.prioridade != 1);
        int numero_aleatorio = (rand() % (max - min + 1)) + min;
        Nos* q;
        q = filaEmergencia->ini;
        while(q!=NULL){
            if(numero_aleatorio == q->info.id){
                while(numero_aleatorio == q->info.id){
                numero_aleatorio = (rand() % (max - min + 1)) + min;
                }
            q = q->prox;
            }
        }
        q = filaNormal->ini;
        while(q!=NULL){
            if(numero_aleatorio == q->info.id){
                while(numero_aleatorio == q->info.id){
                numero_aleatorio = (rand() % (max - min + 1)) + min;
                }
            q = q->prox;
            }
        }
        q = filaAtendidos->ini;
        while(q!=NULL){
            if(numero_aleatorio == q->info.id){
                while(numero_aleatorio == q->info.id){
                numero_aleatorio = (rand() % (max - min + 1)) + min;
                }
            q = q->prox;
            }
        }
        novoPet.id = numero_aleatorio;
        printf("\nO ID gerado para o PET é: %d\n", novoPet.id);

        printf("\n--- Você adicionou o PET com os seguintes dados: ---\n");
        imprimeInfopet(novoPet);
        printf("\n--- Você confirma as informações do PET ou deseja refazer?(0-Refazer/1-Confirmar): ");
        scanf("%d", &confirmar);
    }

    novoPet.prioridade == 0 ? InsereFila(filaEmergencia,novoPet) : InsereFila(filaNormal,novoPet);

    printf("\n--- PET adicionado com sucesso! ---\n");
    printf("\n--- Aperte qualquer tecla para continuar ---");

    getchar();

    return novoPet;
}

void atenderPet(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos){
    Pet petAtendido;
    limparTela();
    printf("--- Você está no menu de Atender um PET ---\n");

    if(!VaziaFila(filaEmergencia)){
        printf("\n --- Atendendo o próximo PET da Emergência ---\n");
        petAtendido = RetiraFila(filaEmergencia);
        printf("\n--- Dados do PET sendo atendido: ---\n");
        imprimeInfopet(petAtendido);
        InsereFila(filaAtendidos, petAtendido);
        printf("\n--- PET atendido com sucesso! ---\n");
        printf("\n--- Aperte qualquer tecla para continuar ---");
        limpar_buffer();
        getchar();
    }else if(!VaziaFila(filaNormal)){
        printf("\n --- Atendendo o próximo PET da fila Normal ---\n");
        petAtendido = RetiraFila(filaNormal);
        printf("\n--- Dados do PET sendo atendido: ---\n");
        imprimeInfopet(petAtendido);
        InsereFila(filaAtendidos, petAtendido);
        printf("\n--- PET atendido com sucesso! ---\n");
        printf("\n--- Aperte qualquer tecla para continuar ---");
        limpar_buffer();
        getchar();
    }else{
        printf("\n--- Não há PETs para serem Atendidos! ---\n");
        printf("\n --- Aperte qualquer tecla para continuar ---\n");
        limpar_buffer();
        getchar();
    }
}

void buscarPet(Fila* filaEmergencia, Fila* filaNormal, Fila* filaAtendidos){
    int tipo_Busca, encontrado=0;
    limparTela();
    printf("--- Você está no menu de Buscar um PET ---\n");
    printf("\nDigite o tipo de busca que deseja realizar (0-Por ID/1-Por Nome): ");
    scanf("%d", &tipo_Busca);
    if(tipo_Busca){
        char nome_Busca[51];
        printf("\nDigite o nome do PET que deseja buscar: ");
        limpar_buffer();
        fgets(nome_Busca, 51, stdin);
        nome_Busca[strcspn(nome_Busca, "\n")] = 0;

        Nos* q;
        printf("\n--- Buscando PETs com o nome: %s ---\n", nome_Busca);
        //Começar a percorrer as filas para achar o nome
        q = filaEmergencia->ini;
        while(q != NULL){
            if(strcmp(q->info.nome, nome_Busca) == 0){
                printf("\n--- PET encontrado na fila de Emergência! ---\n");
                imprimeInfopet(q->info);
                encontrado =1;
                printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                limpar_buffer();
                getchar();
            }
            q = q->prox;
        }
            q = filaNormal->ini;
            while(q!= NULL){
                if(strcmp(q->info.nome, nome_Busca) == 0){
                    printf("\n--- PET encontrado na fila Normal! ---\n");
                    imprimeInfopet(q->info);
                    encontrado =1;
                    printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                    limpar_buffer();
                    getchar();
                }
                q = q->prox;
            }
            q = filaAtendidos->ini;
            while(q!= NULL){
                if(strcmp(q->info.nome, nome_Busca) == 0){
                    printf("\n--- PET encontrado na fila de Atendidos! ---\n");
                    imprimeInfopet(q->info);
                    encontrado =1;
                    printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                    limpar_buffer();
                    getchar();
                }
                q = q->prox;
            }
    }else if(!tipo_Busca){
        int id_Procurado;
        printf("\nDigite o ID do PET que deseja buscar: ");
        scanf("%d",&id_Procurado);
        Nos* q;
        printf("\n--- Buscando PETs com o ID: %d ---\n", id_Procurado);
        //Começar a percorrer as filas para achar o nome
        q = filaEmergencia->ini;
        while(q != NULL){
            if(id_Procurado == q->info.id){
                printf("\n--- PET encontrado na fila de Emergência! ---\n");
                imprimeInfopet(q->info);
                encontrado =1;
                printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                limpar_buffer();
                getchar();
            }
            q = q->prox;
        }
            q = filaNormal->ini;
            while(q!= NULL){
                if(id_Procurado == q->info.id){
                    printf("\n--- PET encontrado na fila Normal! ---\n");
                    imprimeInfopet(q->info);
                    encontrado =1;
                    printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                    limpar_buffer();
                    getchar();
                }
                q = q->prox;
            }
            q = filaAtendidos->ini;
            while(q!= NULL){
                if(id_Procurado == q->info.id){
                    printf("\n--- PET encontrado na fila de Atendidos! ---\n");
                    imprimeInfopet(q->info);
                    encontrado =1;
                    printf("\n--- Aperte qualquer tecla para continuar! ---\n");
                    limpar_buffer();
                    getchar();
                }
                q = q->prox;
            }

    }else{
        printf("Erro!");
        limpar_buffer();
        getchar();
    }
    if(!encontrado){
        printf("\n--- O PET não foi identificado em nenhuma das FILAS! ---\n");
         limpar_buffer();
        getchar();
    }
}

void imprimirFila(Fila* filaDesejada){

    Nos* q;
    q = filaDesejada->ini;


    while(q!=NULL){
    imprimeInfopet(q->info);
    q=q->prox;
    printf("\n");
    }
    limpar_buffer();
    getchar();

}

void imprimirRelatorio(Fila* filaEmergencia, Fila* filaNormal){
    limparTela();
    printf("\n--- Você está no menu do Relatório das FILAS! ---\n");
    printf("\n--- Deseja imprimir o relatório de qual fila? ---\n");
    printf("\n--- (0)Fila de Emergência ---");
    printf("\n--- (1)Fila Normal ---");
    printf("\n--- (2)Ambas as filas ---\n");
    int opcao;
    scanf("%d",&opcao);
    switch(opcao){
        case 0:
            limparTela();
            printf("\n--- Relatório da Fila de Emergência ---\n");
            imprimirFila(filaEmergencia);
            printf("\n\n\n\n");
            break;
        case 1:
            limparTela();
            printf("\n--- Relatório da Fila de Normal ---\n");
            imprimirFila(filaNormal);
            break;
        case 2:
            limparTela();
            printf("\n--- Relatório da Fila de Emergência ---\n");
            imprimirFila(filaEmergencia);
            printf("\n\n--- Relatório da Fila de Normal ---\n");
            imprimirFila(filaNormal);
            break;
    }

}

void prox_Pet(Fila* filaEmergencia, Fila* filaNormal){

    limparTela();
    printf("--- Você está no menu do Próximo PET a ser atendido! ---\n");

    if(!VaziaFila(filaEmergencia)){
        printf("\n --- O próximo PET a ser atendido é da Emergêmncia ---\n");
        imprimeInfopet(filaEmergencia->ini->info);
        printf("\n --- Aperte qualquer tecla para continuar ---\n");
        limpar_buffer();
        getchar();
    }else if(!VaziaFila(filaNormal)){
        printf("\n --- O próximo PET a ser atendido é da fila Normal ---\n");
        imprimeInfopet(filaNormal->ini->info);
        printf("\n --- Aperte qualquer tecla para continuar ---\n");
        limpar_buffer();
        getchar();
    }else{
        printf("\n--- Não há PETs para serem Atendidos! ---n");
        printf("\n--- Aperte qualquer tecla para continuar ---\n");
        limpar_buffer();
        getchar();
    }
}

void imprimir_Atendidos(Fila* filaAtendidos){
    limparTela();
    printf("\n--- Relatório da Fila de Atendidos ---\n");
    imprimirFila(filaAtendidos);
    printf("\n--- Pressione qualquer tecla para continuar ---\n");
    limpar_buffer();
    getchar();
}

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opr=0;

    Fila* filaEmergencia = CriaFila();
    Fila* filaNormal = CriaFila();
    Fila* filaAtendidos = CriaFila();

     // Carrega os dados do arquivo ao iniciar o programa
    carregar_dados(filaEmergencia, filaNormal, filaAtendidos);
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();


    do{
        limparTela();
        printf("\n          --- Menu de Opções ---\n");
        printf("\n--- (1)Adicionar PET a fila ---");
        printf("\n--- (2)Atender PET ---");
        printf("\n--- (3)Buscar PET ---");
        printf("\n--- (4)Relatório da FILA ---");
        printf("\n--- (5)Próximo PET a ser atendido ---");
        printf("\n--- (6)Relatório já Atendidos ---");
        printf("\n--- (7)Finalizar Sistema ---\n");

        scanf("%d",&opr);

        switch(opr){
            case 1:
                //Adiciona PET a fila
                adicionarPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 2:
                //Atender PET
                atenderPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 3:
                //Buscar PET
                buscarPet(filaEmergencia, filaNormal, filaAtendidos);
                break;
            case 4:
                //Relatório da FILA
                imprimirRelatorio(filaEmergencia, filaNormal);
                break;
            case 5:
                //Próximo PET a ser atendido
                prox_Pet(filaEmergencia, filaNormal);
                break;
            case 6:
                imprimir_Atendidos(filaAtendidos);
                //Relatório já Atendidos
                break;
            case 7:
                //Finalizar Sistema
                break;
            default:
                //Opção Inválida

        }



    }while(opr!=7);

    salvar_dados(filaEmergencia, filaNormal, filaAtendidos);

    // Libera a memória (opcional, mas boa prática)
    liberaFila(filaEmergencia);
    liberaFila(filaNormal);
    liberaFila(filaAtendidos);

    printf("Sistema finalizado.\n");

    return 0;

}
