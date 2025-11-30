#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Opcional para medir tempo, mas não usado aqui para manter simplicidade

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct para Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variáveis globais para vetor
Item inventarioVetor[10];
int numItensVetor = 0;

// Ponteiro para a cabeça da lista encadeada
No* cabecaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Funções para Vetor (Lista Sequencial)

// Função para inserir item no vetor
void inserirItemVetor() {
    if (numItensVetor >= 10) {
        printf("Inventário cheio! Não é possível adicionar mais itens.\n");
        return;
    }
    
    Item novoItem;
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    inventarioVetor[numItensVetor] = novoItem;
    numItensVetor++;
    
    printf("Item adicionado com sucesso!\n");
    listarItensVetor();
}

// Função para remover item do vetor por nome (busca sequencial)
void removerItemVetor() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    int encontrado = 0;
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(inventarioVetor[i].nome, nomeRemover) == 0) {
            for (int j = i; j < numItensVetor - 1; j++) {
                inventarioVetor[j] = inventarioVetor[j + 1];
            }
            numItensVetor--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
    
    listarItensVetor();
}

// Função para listar itens do vetor
void listarItensVetor() {
    if (numItensVetor == 0) {
        printf("Inventário vazio.\n");
        return;
    }
    
    printf("\nItens no inventário (Vetor):\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
               inventarioVetor[i].nome, inventarioVetor[i].tipo, inventarioVetor[i].quantidade);
    }
    printf("\n");
}

// Função para buscar item no vetor por nome (busca sequencial)
void buscarSequencialVetor() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    comparacoesSequencial = 0;  // Reset contador
    int encontrado = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(inventarioVetor[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   inventarioVetor[i].nome, inventarioVetor[i].tipo, inventarioVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
    
    printf("Número de comparações na busca sequencial: %d\n", comparacoesSequencial);
    listarItensVetor();
}

// Função para ordenar o vetor por nome (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(inventarioVetor[j].nome, inventarioVetor[j + 1].nome) > 0) {
                Item temp = inventarioVetor[j];
                inventarioVetor[j] = inventarioVetor[j + 1];
                inventarioVetor[j + 1] = temp;
            }
        }
    }
    
    printf("Vetor ordenado por nome!\n");
    listarItensVetor();
}

// Função para busca binária no vetor (após ordenação)
void buscarBinariaVetor() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar (vetor deve estar ordenado): ");
    scanf("%s", nomeBuscar);
    
    comparacoesBinaria = 0;  // Reset contador
    int esquerda = 0, direita = numItensVetor - 1;
    int encontrado = 0;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(inventarioVetor[meio].nome, nomeBuscar);
        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   inventarioVetor[meio].nome, inventarioVetor[meio].tipo, inventarioVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
    
    printf("Número de comparações na busca binária: %d\n", comparacoesBinaria);
    listarItensVetor();
}

// Funções para Lista Encadeada

// Função para inserir item na lista (no final)
void inserirItemLista() {
    Item novoItem;
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novoNo->dados = novoItem;
    novoNo->proximo = NULL;
    
    if (cabecaLista == NULL) {
        cabecaLista = novoNo;
    } else {
        No* temp = cabecaLista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
    }
    
    printf("Item adicionado com sucesso!\n");
    listarItensLista();
}

// Função para remover item da lista por nome
void removerItemLista() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    No* atual = cabecaLista;
    No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            if (anterior == NULL) {
                cabecaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
    
    listarItensLista();
}

// Função para listar itens da lista
void listarItensLista() {
    if (cabecaLista == NULL) {
        printf("Inventário vazio.\n");
        return;
    }
    
    printf("\nItens no inventário (Lista Encadeada):\n");
    No* temp = cabecaLista;
    while (temp != NULL) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
               temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
    printf("\n");
}

// Função para buscar item na lista por nome (busca sequencial)
void buscarSequencialLista() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    comparacoesSequencial = 0;  // Reset contador
    No* temp = cabecaLista;
    int encontrado = 0;
    
    while (temp != NULL) {
        comparacoesSequencial++;
        if (strcmp(temp->dados.nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
            encontrado = 1;
            break;
        }
        temp = temp->proximo;
    }
    
    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
    
    printf("Número de comparações na busca sequencial: %d\n", comparacoesSequencial);
    listarItensLista();
}

// Função principal com menus
int main() {
    int estrutura, opcao;
    
    while (1) {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1. Vetor (Lista Sequencial)\n");
        printf("2. Lista Encadeada\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &estrutura);
        
        while (getchar() != '\n');  // Limpa buffer
        
        if (estrutura == 3) {
            printf("Saindo...\n");
            exit(0);
        }
        
        if (estrutura == 1) {  // Vetor
            while (1) {
                printf("\nMenu Vetor - Escolha uma operação:\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (sequencial)\n");
                printf("5. Ordenar vetor por nome\n");
                printf("6. Buscar item (binária - após ordenação)\n");
                printf("7. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);
                
                while (getchar() != '\n');
                
                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                    case 7: goto voltar;
                    default: printf("Opção inválida!\n");
                }
            }
        } else if (estrutura == 2) {  // Lista
            while (1) {
                printf("\nMenu Lista - Escolha uma operação:\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar item (sequencial)\n");
                printf("5. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);
                
                while (getchar() != '\n');
                
                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                    case 5: goto voltar;
                    default: printf("Opção inválida!\n");
                }
            }
        } else {
            printf("Opção inválida!\n");
        }
        
        voltar:;  // Label para voltar ao menu principal
    }
    
    return 0;
}
