// By: Gonçalo Leão

#include <climits>

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // TODO

    unsigned int currCand[50];

    for (unsigned int i = 0; i < n; i++) {
        currCand[i] = 0;
    }

    bool foundSol = false;
    unsigned int minCoins = INT_MAX;
    unsigned int currIndex;

    while (true) {
        //variáveis de controlo
        unsigned int totalVal = 0;
        unsigned int totalCoins = 0;

        //vê quais os candidatos de moedas atuais e calcula a soma do seu valor e o número total de moedas usadas
        for (int k = 0; k <n; k++) {
            totalVal += C[k] * currCand[k];
            totalCoins += currCand[k];
        }

        // o algoritmo só é possível porque tudo é inicializado a zero, e só posteriormente é que se atualiza os candidatos de acordo com o stock de moedas
        //Se o valor somado anteriormente for igual ao valor de T atualiza-se o minimo de moedas usadas para a soma feita no ciclo anterior
        if(totalVal == T) {
            //foundsol usado para ver se estamos no primeiro candidato
            if(!foundSol || totalCoins < minCoins) {
                minCoins = totalCoins;
                foundSol = true;
                //atualiza-se  a array das moedas usadas
                for(int k=0; k<n;k++) {
                    usedCoins[k] = currCand[k];
                }
            }
        }

        // coloca o currIndex a 0;
        currIndex = 0;

        //coloca os candidatos igual ao stock atual
        while (currCand[currIndex] == Stock[currIndex]) {
            currIndex++;
            //para se se ultrapassar o máximo de moedas existentes
            if(currIndex == n) {
                break;
            }
        }

        //para-se o ciclo se o indice atual for superior ao indice maximo da array das moedas
        if (currIndex == n) {
            break;
        }

        // coloca os candidatos a 0 até ao indice atual
        for ( int i = 0; i < currIndex; i++) {
            currCand[i] = 0;
        }

        //atualiza o número de moedas usadas do indice atual
        currCand[currIndex]++;

    }


    return foundSol;
}




bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {

    unsigned int totalVal = 0;
    unsigned int minCoins = INT_MAX;
    unsigned int currItem = n-1;

    unsigned int currCand[50];



    while(totalVal < T) {

    }


    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}

TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}