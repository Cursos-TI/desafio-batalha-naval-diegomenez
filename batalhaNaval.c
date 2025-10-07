#include <stdio.h>

// --- Definição de Constantes ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    
    //======================================================================
    // 1. Criar um Tabuleiro 10x10 
    //======================================================================
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;
    
    // Inicializa o tabuleiro com água
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    //======================================================================
    // 2. Posicionar Quatro Navios 
    //======================================================================
    
    printf("Posicionando quatro navios de tamanho %d...\n", TAMANHO_NAVIO);

    // --- Navio 1: POSIÇÃO HORIZONTAL ---
    // Coordenadas: (2,2), (2,3), (2,4)
    int navio_h_linha = 2;
    int navio_h_coluna = 2;
    for (j = 0; j < TAMANHO_NAVIO; j++) {
        tabuleiro[navio_h_linha][navio_h_coluna + j] = NAVIO;
    }

    // --- Navio 2: POSIÇÃO VERTICAL ---
    // Coordenadas: (5,7), (6,7), (7,7)
    int navio_v_linha = 5;
    int navio_v_coluna = 7;
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio_v_linha + i][navio_v_coluna] = NAVIO;
    }

    // --- Navio 3: POSIÇÃO DIAGONAL (Principal) ---
    
    int navio_d1_linha = 4;
    int navio_d1_coluna = 0;
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        // A linha e a coluna são incrementadas pelo contador do loop 'i'.
        tabuleiro[navio_d1_linha + i][navio_d1_coluna + i] = NAVIO;
    }

    // --- Navio 4: POSIÇÃO DIAGONAL (Secundária ou Anti-diagonal) ---
  
    int navio_d2_linha = 0;
    int navio_d2_coluna = 9;
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        // A linha aumenta com 'i', enquanto a coluna diminui com 'i'.
        tabuleiro[navio_d2_linha + i][navio_d2_coluna - i] = NAVIO;
    }
    
    printf("Navios posicionados!\n\n");

    //======================================================================
    // 3. Exibir o Tabuleiro 
    //======================================================================

    printf("=== Tabuleiro Final de Batalha Naval ===\n");
    printf("Legenda: %d = Agua | %d = Navio\n\n", AGUA, NAVIO);

    // Imprime o cabeçalho das colunas (1 a 10)
    printf("  "); 
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d", j + 1);
    }
    printf("\n");

    // Imprime as linhas com seus índices e conteúdo
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", 'a' + i); // Índice da linha ('a', 'b', ...)
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}