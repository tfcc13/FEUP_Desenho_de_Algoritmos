#include "exercises.h"

unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {

    int max_value_dp_table[100][101];

    //step1

    //preenche a 0 a primeira linha

    for (int i = 0; i < maxWeight; i++) {
        if(i >= weights[0]) {
            max_value_dp_table[0][i] = values[0];
        }
        else {
            max_value_dp_table[0][i] = 0;
        }
    }

    //preenche a 0 a primeira coluna
    for(int i = 1; i<= n; i++) {
        max_value_dp_table[i][0] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for (int w = 1; w <= maxWeight; w++) {

            // Item não cabe na mochila

            if(w <= weights[i]) {
                // o valor atual da table será igual ao último valor máximo
                max_value_dp_table[i][w] = max_value_dp_table[i-1][w];
            }

            //item cabe na mochila
            else {
                // var auxiliar para ver o resultado da soma o item atual com o valor máximo anterior(i-1)
                int aux = values[i]+max_value_dp_table[i-1][w-weights[i]];

                // se esse resultado é maior que o valor maximo anterior
                if(aux > max_value_dp_table[i-1][w]) {
                    //atualiza-se o valor maximo da tabela no item atual
                    max_value_dp_table[i][w] = aux;
                }
                //se esse resultado é inferior ou igual então o valor maximo atual é igual ao
                //valor máximo anterior (i-1)
                else {
                    max_value_dp_table[i][w] = max_value_dp_table[i-1][w];
                }
            }

        }
    }

    //Reconstrução da solução do fim para o início

    // colocar a array dos itens usados a falso
    for(int i = 0; i < n; i++) {
        usedItems[i] = false;
    }


    // copia do maxWeight para usar como indice

    int remainingWeight = maxWeight;

    // item atual, que é o último item, que corresponderá ao valor máximo e ao peso máximo usado
    int currItem = n-1;

    //iterar sobre a matriz
    for(int i = n-1; i > 0; i--) {

        // caso em que já não há mais capacidade
        if(remainingWeight == 0) {
            break;
        }

        // se o valor da capacidade atual  é diferente do valor anterior
        if(max_value_dp_table[i][remainingWeight] != max_value_dp_table[i-1][remainingWeight]) {

            //então o item atual foi usado
            usedItems[i] = true;

            // a capacidade restant atual é igual a capacidade atual
            remainingWeight = weights[i];

            // passa para outro item
            currItem--;
        }


        // se a capacidade atual é maior que 0, então significa que o primeiro item foi usado

        if(remainingWeight > 0 ) {
            usedItems[0] = true;
        }

    }

    return max_value_dp_table[n-1][maxWeight];
}

// COMPLEXIDADE TEMPORAL E ESPACIAL É IGUAL A O(n * maxWeight) +- n^2 dependendo do numero de itens e da capacidade da mochila)

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex2, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP5_Ex2, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}