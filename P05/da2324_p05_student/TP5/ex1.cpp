#include "exercises.h"
#include <iostream>

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int min_coins_table[10][11][1001]; //1col -> moedas, 2col-> moedas 3col -> troco
    int last_coin_table[10][11][1001];
    unsigned int MAX_N_COINS = T+1; // valor auxiliar >  T

    // caso nao seja necessário dar troco
    // inicializa os primeiros valores das células a 0 e os restantes a um valor que nunca será solução
    for (unsigned int i = 0; i < n; i++) {
        for( unsigned int s = 0; s<= Stock[i]; s++){
            min_coins_table[i][s][0] = 0;
            for(unsigned int k = 1; k <= T; k++) {
                min_coins_table[i][s][k] = MAX_N_COINS;
            }
        }

    }

    //caso haja troco para dar e começa pela moeda mais baixa
    //Percorro todos os valores possíveis de stock para uma moeda
    // se Stock[0] =  10 s toma os valores de 1 a 10,
    for (unsigned int s = 1; s <= Stock[0]; s++) {
        // para o 1º valor da moeda
        for (unsigned int k = C[0]; k<= T; k++){
            if(k%C[0]== 0 && k / C[0] <= s) {
                min_coins_table[0][s][k] = k/C[0]; // dá a quantidade de moedas usadas
                last_coin_table[0][s][k] = 0;
            }
        }
    }


    //caso as moedas menores não tenham sido suficientes e ainda haja troco para dar passamos para moedas maior
    for (unsigned int i = 1; i <n; i++) {

        for(unsigned int k = 1; k<= T; k++) {
            min_coins_table[i][0][k] = min_coins_table[i-1][Stock[i-1]][k];
            last_coin_table[i][0][k] = last_coin_table[i-1][Stock[i-1]][k];
        }

        for(unsigned int s=1; s <= Stock[i]; s++) {
            for(unsigned int k = 1; k<= T; k++) {
                //verifico se o meuu k é maior que C[i],
                if(k>=C[i]) { //  se verdade ppoosso usar a moeda i-th;
                    //verifico com a mesma moeda com um stock inferior e se ja tenho a sub solução ai
                    if(min_coins_table[i][s-1][k-C[i]]<min_coins_table[i-1][Stock[i-1]][k]) {
                        min_coins_table[i][s][k] = 1 + min_coins_table[i][s - 1][k - C[i]];
                        last_coin_table[i][s][k] = i;
                    }
                    else{
                        min_coins_table[i][s][k] = min_coins_table[i-1][Stock[i-1]][k];
                        last_coin_table[i][s][k] = last_coin_table[i-1][Stock[i-1]][k];
                    }
                }
                else{
                    min_coins_table[i][s][k] = min_coins_table[i-1][Stock[i-1]][k];
                    last_coin_table[i][s][k] = last_coin_table[i-1][Stock[i-1]][k];
                }
            }

        }
    }


    if(min_coins_table[n-1][Stock[n-1]][T]==MAX_N_COINS) {
        return false;
    }

    for(unsigned int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }

    unsigned  int remainingT = T;

    unsigned int curInd = n-1;
    unsigned int StockInd = Stock[n-1];

    while (remainingT > 0) {
        int next = last_coin_table[curInd][StockInd][remainingT];
        usedCoins[next]++;
        remainingT = C[next];
        curInd = next;
        StockInd = Stock[curInd]-usedCoins[curInd];
    }

    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex1, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];
    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP5_Ex1, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP5_Ex1, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}