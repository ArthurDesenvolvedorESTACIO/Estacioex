#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
// Esta struct representa um item no inventário, contendo nome, tipo e quantidade.
// Campos:
// - nome: string de até 29 caracteres (mais o terminador nulo).
// - tipo: string de até 19 caracteres (mais o terminador nulo).
// - quantidade: inteiro representando a quantidade do item.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor global para armazenar até 10 itens.
// Usamos um vetor fixo para simplicidade, conforme os requisitos.
Item inventario[10];

// Variável global para controlar o número de itens no inventário.
// Inicializada em 0, incrementada ao inserir e decrementada ao remover.
int numItens = 0;

// Função para inserir um item no inventário.
// Verifica se há espaço (máximo 10 itens).
// Solicita ao usuário nome, tipo e quantidade.
// Usa fgets para capturar strings com espaços, removendo o '\n'.
// Retorna 1 se inserido com sucesso, 0 se inventário cheio.
int inserirItem() {
    if (numItens >= 10) {
        printf("Inventário cheio! Não é possível adicionar mais itens.\n");
        return 0;
    }

    Item novoItem;
    printf("Digite o nome do item (até 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    // Remove o '\n' do final da string
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura, até 19 caracteres): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    // Limpa o buffer de entrada após scanf
    getchar();

    // Adiciona o item ao vetor
    inventario[numItens] = novoItem;
    numItens++;
    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
    return 1;
}

// Função para remover um item do inventário pelo nome.
// Realiza busca sequencial no vetor.
// Se encontrado, remove deslocando os itens subsequentes.
// Retorna 1 se removido, 0 se não encontrado.
int removerItem() {
    if (numItens == 0) {
        printf("Inventário vazio! Não há itens para remover.\n");
        return 0;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    // Busca sequencial pelo nome
    for (int i = 0; i < numItens; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            // Remove deslocando os itens
            for (int j = i; j < numItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            numItens--;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            return 1;
        }
    }
    printf("Item '%s' não encontrado no inventário.\n", nomeRemover);
    return 0;
}

// Função para listar todos os itens no inventário.
// Percorre o vetor e imprime os dados de cada item.
// Se vazio, informa ao usuário.
void listarItens() {
    if (numItens == 0) {
        printf("Inventário vazio!\n");
        return;
    }

    printf("Itens no inventário:\n");
    for (int i = 0; i < numItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
}

// Função para buscar um item pelo nome.
// Realiza busca sequencial no vetor.
// Se encontrado, exibe os dados; caso contrário, informa não encontrado.
void buscarItem() {
    if (numItens == 0) {
        printf("Inventário vazio! Não há itens para buscar.\n");
        return;
    }

    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    // Busca sequencial
    for (int i = 0; i < numItens; i++) {
        if (strcmp(inventario[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
            return;
        }
    }
    printf("Item '%s' não encontrado no inventário.\n", nomeBuscar);
}

// Função principal: menu interativo.
// Exibe opções ao usuário e chama as funções correspondentes.
// Loop até o usuário escolher sair.
// Após cada operação, lista os itens automaticamente.
int main() {
    int opcao;
    while (1) {
        printf("\n=== Sistema de Inventário ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer após scanf

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        // Após cada operação (exceto sair), lista os itens
        if (opcao != 5) {
            printf("\n--- Itens atuais no inventário ---\n");
            listarItens();
        }
    }
    return 0;
}