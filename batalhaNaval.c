
#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs() (valor absoluto)

// --- Definição de Constantes ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5 // Usaremos 5x5 para as matrizes de habilidade

// Valores para representar os elementos no tabuleiro
#define AGUA 0
#define NAVIO 3
#define EFEITO 5 // Área afetada por uma habilidade

// Protótipo da função que vamos criar
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                       int origem_linha, int origem_coluna);

void exibirMatrizHabilidade(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], const char* nome);

int main() {
    //======================================================================
    // 1. Definir o Tabuleiro e Posicionar Navios (Base)
    //======================================================================
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;
    
    // Inicializa o tabuleiro com água e posiciona os navios de antes
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    // (Opcional) Adicionando um navio para ver a interação
    tabuleiro[5][5] = NAVIO; tabuleiro[5][6] = NAVIO; tabuleiro[5][7] = NAVIO;

    //======================================================================
    // 2. Criar Matrizes de Habilidade (Dinamicamente)
    //======================================================================
    
    // Declara as três matrizes de habilidade 5x5
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    
    int centro = TAMANHO_HABILIDADE / 2; // O centro de uma matriz 5x5 é o índice 2

    // --- Construção da Habilidade CONE ---
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Um cone de 3 linhas de altura
            if (i < 3 && (j >= centro - i && j <= centro + i)) {
                habilidade_cone[i][j] = 1;
            }
        }
    }

    // --- Construção da Habilidade CRUZ ---
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                habilidade_cruz[i][j] = 1;
            }
        }
    }

    // --- Construção da Habilidade OCTAEDRO (Losango/Diamante) ---
    
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade_octaedro[i][j] = 1;
            }
        }
    }

    // Exibe as matrizes de habilidade geradas
    exibirMatrizHabilidade(habilidade_cone, "Cone");
    exibirMatrizHabilidade(habilidade_cruz, "Cruz");
    exibirMatrizHabilidade(habilidade_octaedro, "Octaedro");

    //======================================================================
    // 3. Integrar Habilidades ao Tabuleiro
    //======================================================================

    // Define os pontos de origem (linha, coluna) para cada habilidade no tabuleiro 10x10
    printf("Aplicando habilidades no tabuleiro...\n\n");
    
    // Cone: Origem no topo do tabuleiro para testar limites. O "topo do cone" ficará em (1,4).
    aplicarHabilidade(tabuleiro, habilidade_cone, 1, 4);

    // Cruz: Origem sobre o navio para ver a sobreposição. O "centro da cruz" ficará em (5,6).
    aplicarHabilidade(tabuleiro, habilidade_cruz, 5, 6);

    // Octaedro: Origem no canto inferior direito para testar limites. O "centro" ficará em (8,8).
    aplicarHabilidade(tabuleiro, habilidade_octaedro, 8, 8);


    //======================================================================
    // 4. Exibir o Tabuleiro Final com Habilidades
    //======================================================================
    printf("=== Tabuleiro Final com Efeitos ===\n");
    printf("Legenda: ~ = Agua | N = Navio | * = Area de Efeito\n\n");

    printf("  "); 
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d", j + 1);
    }
    printf("\n");

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", 'a' + i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo = ' ';
            switch (tabuleiro[i][j]) {
                case AGUA:   simbolo = '~'; break;
                case NAVIO:  simbolo = 'N'; break;
                case EFEITO: simbolo = '*'; break;
            }
            printf(" %c", simbolo);
        }
        printf("\n");
    }

    return 0;
}

/**
 * @brief Sobrepõe uma matriz de habilidade no tabuleiro principal.
 * * @param tabuleiro O tabuleiro 10x10 do jogo.
 * @param habilidade A matriz 5x5 da habilidade (o "molde").
 * @param origem_linha A linha no tabuleiro principal onde o centro da habilidade será aplicado.
 * @param origem_coluna A coluna no tabuleiro principal onde o centro da habilidade será aplicado.
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], 
                       int origem_linha, int origem_coluna) {
    
    int centro = TAMANHO_HABILIDADE / 2;
    int i, j;

    // Percorre a matriz de habilidade 5x5
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Se a posição atual da habilidade não tem efeito (é 0), ignora.
            if (habilidade[i][j] == 0) {
                continue;
            }

            // Calcula a posição correspondente no tabuleiro principal.
            // A fórmula usa o offset da posição atual [i][j] em relação ao centro da habilidade.
            int linha_no_tabuleiro = origem_linha + (i - centro);
            int coluna_no_tabuleiro = origem_coluna + (j - centro);

            // Requisito: Validação para não "desenhar" fora do tabuleiro.
            if (linha_no_tabuleiro >= 0 && linha_no_tabuleiro < TAMANHO_TABULEIRO &&
                coluna_no_tabuleiro >= 0 && coluna_no_tabuleiro < TAMANHO_TABULEIRO) {
                
                // Marca a posição no tabuleiro com o valor de EFEITO.
                tabuleiro[linha_no_tabuleiro][coluna_no_tabuleiro] = EFEITO;
            }
        }
    }
}

/**
 * @brief Função auxiliar para exibir uma matriz de habilidade formatada.
 */
void exibirMatrizHabilidade(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], const char* nome) {
    printf("--- Habilidade: %s ---\n", nome);
    int i, j;
    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}