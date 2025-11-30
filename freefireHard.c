#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5, onde 1 é a mais alta
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[10];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    limparTela();
    printf("=== Código da Ilha – Edição Free Fire ===\n");
    printf("Nível: Mestre\n");
    printf("Itens na mochila: %d/10\n", numItens);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "Sim" : "Não");
    printf("\nMenu principal:\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens por critério (nome, tipo, prioridade)\n");
    printf("5. Realizar busca binária por nome\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= 10) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do item (até 29 caracteres): ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura, até 19 caracteres): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    printf("Digite a prioridade (1 a 5, onde 1 é a mais alta): ");
    scanf("%d", &novoItem.prioridade);
    getchar(); // Limpa buffer

    // Valida prioridade
    if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
        printf("Prioridade inválida! Deve ser entre 1 e 5.\n");
        return;
    }

    mochila[numItens] = novoItem;
    numItens++;
    ordenadaPorNome = false; // Inserção desordena por nome
    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    if (numItens == 0) {
        printf("Mochila vazia! Não há itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Remove deslocando
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            ordenadaPorNome = false; // Remoção pode desordenar
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            return;
        }
    }
    printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("Itens na mochila:\n");
    printf("%-30s %-20s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-30s %-20s %-10d %-10d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("Mochila vazia! Não há itens para ordenar.\n");
        return;
    }

    int opcao;
    printf("Escolha o critério de ordenação:\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Prioridade\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa buffer

    CriterioOrdenacao criterio;
    switch (opcao) {
        case 1:
            criterio = NOME;
            ordenadaPorNome = true;
            break;
        case 2:
            criterio = TIPO;
            ordenadaPorNome = false;
            break;
        case 3:
            criterio = PRIORIDADE;
            ordenadaPorNome = false;
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    comparacoes = 0; // Reseta contador
    insertionSort(criterio);
    printf("Ordenação concluída com %d comparações.\n", comparacoes);
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio) {
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        // Comparação baseada no critério
        while (j >= 0) {
            bool deveTrocar = false;
            comparacoes++; // Conta cada comparação

            if (criterio == NOME) {
                if (strcmp(mochila[j].nome, chave.nome) > 0) {
                    deveTrocar = true;
                }
            } else if (criterio == TIPO) {
                if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                    deveTrocar = true;
                }
            } else if (criterio == PRIORIDADE) {
                if (mochila[j].prioridade > chave.prioridade) { // Prioridade menor número é maior prioridade
                    deveTrocar = true;
                }
            }

            if (!deveTrocar) break;

            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("A mochila deve estar ordenada por nome para realizar busca binária.\n");
        return;
    }

    if (numItens == 0) {
        printf("Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    char nomeBuscar[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    int esquerda = 0, direita = numItens - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBuscar);
        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Item '%s' não encontrado na mochila.\n", nomeBuscar);
}

int main() {
    int opcao;
    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

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
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("Saindo do jogo...\n");
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        // Pausa para o usuário ver o resultado
        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}
