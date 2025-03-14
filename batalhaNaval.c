#include <stdio.h>

// Tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10

// Tamanho dos navios
#define TAMANHO_NAVIO 3

// Valor que representa água no tabuleiro
#define AGUA 0

// Valor que representa uma parte de um navio no tabuleiro
#define NAVIO 3

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se as coordenadas estão dentro dos limites do tabuleiro
int coordenadaValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se um navio pode ser posicionado horizontalmente
int posicaoHorizontalValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as coordenadas iniciais são válidas
    if (!coordenadaValida(linha, coluna) || !coordenadaValida(linha, coluna + TAMANHO_NAVIO - 1)) {
        return 0; // Fora dos limites
    }

    // Verifica se as posições estão livres (não há sobreposição)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) {
            return 0; // Sobreposição detectada
        }
    }

    return 1; // Posição válida
}

// Função para verificar se um navio pode ser posicionado verticalmente
int posicaoVerticalValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as coordenadas iniciais são válidas
    if (!coordenadaValida(linha, coluna) || !coordenadaValida(linha + TAMANHO_NAVIO - 1, coluna)) {
        return 0; // Fora dos limites
    }

    // Verifica se as posições estão livres (não há sobreposição)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) {
            return 0; // Sobreposição detectada
        }
    }

    return 1; // Posição válida
}

// Função para posicionar um navio horizontalmente
void posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Função para posicionar um navio verticalmente
void posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais do navio horizontal
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;

    // Verifica se o navio horizontal pode ser posicionado
    if (posicaoHorizontalValida(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal)) {
        posicionarNavioHorizontal(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal);
    } else {
        printf("Erro: Navio horizontal não pode ser posicionado nas coordenadas (%d, %d).\n", linhaNavioHorizontal, colunaNavioHorizontal);
        return 1; // Encerra o programa com erro
    }

    // Coordenadas iniciais do navio vertical
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;

    // Verifica se o navio vertical pode ser posicionado
    if (posicaoVerticalValida(tabuleiro, linhaNavioVertical, colunaNavioVertical)) {
        posicionarNavioVertical(tabuleiro, linhaNavioVertical, colunaNavioVertical);
    } else {
        printf("Erro: Navio vertical não pode ser posicionado nas coordenadas (%d, %d).\n", linhaNavioVertical, colunaNavioVertical);
        return 1; // Encerra o programa com erro
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}