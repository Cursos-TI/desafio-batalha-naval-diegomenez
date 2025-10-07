#include <stdio.h>

// --- Definição de Constantes ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    
    //======================================================================
    // 1. Represente o Tabuleiro 
    //======================================================================
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;
    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    //======================================================================
    // 2. Posicione os Navios 
    //======================================================================
    // Navio 1: POSIÇÃO HORIZONTAL
    int navio_h_linha = 2;
    int navio_h_coluna = 2;
    for (j = 0; j < TAMANHO_NAVIO; j++) {
        tabuleiro[navio_h_linha][navio_h_coluna + j] = NAVIO;
    }

    // Navio 2: POSIÇÃO VERTICAL
    int navio_v_linha = 5;
    int navio_v_coluna = 7;
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio_v_linha + i][navio_v_coluna] = NAVIO;
    }

    //======================================================================
    // 3. Exiba o Tabuleiro 
    //======================================================================

    printf("=== Tabuleiro Final de Batalha Naval ===\n");
    printf("Legenda: %d = Agua | %d = Navio\n\n", AGUA, NAVIO);

    
    printf("  "); 
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        
        printf("%2d", j + 1);
    }
    printf("\n"); 

    
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        
        printf("%c ", 'a' + i);

        
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
           
            printf(" %d", tabuleiro[i][j]);
        }
        
        printf("\n");
    }

    return 0;
}