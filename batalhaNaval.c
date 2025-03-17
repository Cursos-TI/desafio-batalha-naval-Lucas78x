#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// Função para inicializar o tabuleiro com valores de AGUA (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se uma coordenada está dentro dos limites do tabuleiro
int coordenadaValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se a posição horizontal é válida para o navio
int posicaoHorizontalValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (!coordenadaValida(linha, coluna) || !coordenadaValida(linha, coluna + TAMANHO_NAVIO - 1)) {
        return 0; // Fora dos limites
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) {
            return 0; // Sobreposição
        }
    }

    return 1; // Valido
}

// Função para verificar se a posição vertical é válida para o navio
int posicaoVerticalValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (!coordenadaValida(linha, coluna) || !coordenadaValida(linha + TAMANHO_NAVIO - 1, coluna)) {
        return 0; // Fora dos limites
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) {
            return 0; // Sobreposição
        }
    }

    return 1; // Valido
}

// Função para verificar se a posição diagonal é válida para o navio
int posicaoDiagonalValida(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha + i;
        int novaColuna = (diagonal == 1) ? coluna + i : coluna - i;

        if (!coordenadaValida(novaLinha, novaColuna) || tabuleiro[novaLinha][novaColuna] != AGUA) {
            return 0; // Fora dos limites ou sobreposição
        }
    }

    return 1; // Valido
}

// Função para posicionar o navio horizontalmente no tabuleiro
void posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Função para posicionar o navio verticalmente no tabuleiro
void posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
}

// Função para posicionar o navio na diagonal no tabuleiro
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha + i;
        int novaColuna = (diagonal == 1) ? coluna + i : coluna - i;
        tabuleiro[novaLinha][novaColuna] = NAVIO;
    }
}
// Função para criar a matriz de Cone
void gerarCone(int habilidade[5][5]) {
    // Forma de cone (expansão de 1 para baixo)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de Cruz
void gerarCruz(int habilidade[5][5]) {
    // Forma de cruz (linha vertical e horizontal no meio)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de Octaedro
void gerarOctaedro(int habilidade[5][5]) {
    // Forma de octaedro (losango)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i + j >= 2 && i + j <= 6 && j - i <= 2 && i - j <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][5], int linhaOrigem, int colunaOrigem) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linhaTabuleiro = linhaOrigem - 2 + i;
            int colunaTabuleiro = colunaOrigem - 2 + j;
            if (habilidade[i][j] == 1 && linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO && colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {
                tabuleiro[linhaTabuleiro][colunaTabuleiro] = AREA_HABILIDADE;
            }
        }
    }
}

// Função para exibir o tabuleiro no formato 10x10
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval:\n");

    // Cabeçalho com os índices das colunas
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d ", j);
    }
    printf("\n");

    // Linha separadora
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");

      // Exibe o conteúdo do tabuleiro
      for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d|", i);  // Exibe o número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" 0 ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" 3 ");
            } else if (tabuleiro[i][j] == AREA_HABILIDADE) {
                printf(" 5 ");
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidadeCone[5][5], habilidadeCruz[5][5], habilidadeOctaedro[5][5];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posicionamento de navios
    if (posicaoHorizontalValida(tabuleiro, 0, 0)) {
        posicionarNavioHorizontal(tabuleiro, 0, 0);
    }

    if (posicaoVerticalValida(tabuleiro, 1, 1)) {
        posicionarNavioVertical(tabuleiro, 1, 1);
    }

    if (posicaoDiagonalValida(tabuleiro, 2, 2, 1)) {
        posicionarNavioDiagonal(tabuleiro, 2, 2, 1);
    }

    if (posicaoDiagonalValida(tabuleiro, 2, 7, 2)) {
        posicionarNavioDiagonal(tabuleiro, 2, 7, 2);
    }

   // Gera as matrizes de habilidades
   gerarCone(habilidadeCone);
   gerarCruz(habilidadeCruz);
   gerarOctaedro(habilidadeOctaedro);

   // Aplica as habilidades no tabuleiro
   aplicarHabilidade(tabuleiro, habilidadeCone, 2, 2);  // Cone no ponto (2, 2)
   aplicarHabilidade(tabuleiro, habilidadeCruz, 4, 4);  // Cruz no ponto (4, 4)
   aplicarHabilidade(tabuleiro, habilidadeOctaedro, 6, 6);  // Octaedro no ponto (6, 6)

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
