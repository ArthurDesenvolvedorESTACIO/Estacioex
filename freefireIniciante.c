#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item conforme solicitado.
// Esta struct representa um item no inventário, agregando dados relacionados: nome, tipo e quantidade.
typedef struct {
    char nome[30];     // Nome do item (até 29 caracteres + null terminator)
    char tipo[20];     // Tipo do item (ex: arma, munição, cura) (até 19 caracteres + null terminator)
    int quantidade;    // Quantidade do item
} Item;

// Vetor global para armazenar até 10 itens.
// Usamos um vetor de structs para organizar os dados sequencialmente.
Item inventario[10];

// Variável global para controlar o número de itens cadastrados.
// Isso facilita a verificação de limites e iteração.
int numItens = 0;

// Função para inserir um novo item no inventário.
// Verifica se há espaço, lê os dados do usuário e adiciona ao vetor.
// Após a inserção, lista os itens para confirmar a operação.
void inserirItem() {
    if (numItens >= 10) {
        printf("Inventário cheio! Não é possível adicionar mais itens.\n");
        return;
    }
    
    Item novoItem;
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);  // Lê o nome (sem espaços para simplificar)
    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);  // Lê o tipo (sem espaços)
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);  // Lê a quantidade
    
    // Adiciona o item ao vetor na posição atual de numItens
    inventario[numItens] = novoItem;
    numItens++;
    
    printf("Item adicionado com sucesso!\n");
    listarItens();  // Lista os itens após a operação
}

// Função para remover um item do inventário pelo nome.
// Realiza uma busca sequencial, remove o item encontrado (deslocando os outros) e atualiza numItens.
// Se não encontrar, informa o usuário.
// Após a remoção, lista os itens.
void removerItem() {
    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nomeRemover);
    
    int encontrado = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            // Remove o item deslocando os elementos subsequentes
            for (int j = i; j < numItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            numItens--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado no inventário.\n");
    }
    
    listarItens();  // Lista os itens após a operação
}

// Função para listar todos os itens cadastrados.
// Percorre o vetor e imprime os dados de cada item.
// Se o inventário estiver vazio, informa o usuário.
void listarItens() {
    if (numItens == 0) {
        printf("Inventário vazio.\n");
        return;
    }
    
    printf("\nItens no inventário:\n");
    for (int i = 0; i < numItens; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
               inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("\n");
}

// Função para buscar um item pelo nome usando busca sequencial.
// Percorre o vetor comparando nomes e exibe os dados se encontrado.
// Se não encontrado, informa o usuário.
// Após a busca, lista os itens (conforme requisito de listagem após operações).
void buscarItem() {
    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBuscar);
    
    int encontrado = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(inventario[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s, Tipo: %s, Quantidade: %d\n", 
                   inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item não encontrado no inventário.\n");
    }
    
    listarItens();  // Lista os itens após a operação
}

// Função principal: controla o fluxo do programa com um menu.
// Usa um laço while para repetir até o usuário escolher sair.
// Limpa o buffer de entrada após leituras para evitar problemas.
int main() {
    int opcao;
    
    // Menu principal com opções claras para o usuário
    while (1) {
        printf("\nSistema de Inventário - Escolha uma opção:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        // Limpa o buffer para evitar problemas com entradas subsequentes
        while (getchar() != '\n');
        
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
    }
    
    return 0;
}
