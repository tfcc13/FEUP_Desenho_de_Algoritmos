// By: Gonçalo Leão

//algoritmo com complexidade n*2^n, itera sobre todos os candidatos possiveis as combinações existente

bool subsetSum(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {

    // variável da soma
    int sum;

    // mask para se saber os índices dos elementos da array que estão a ser usados
    bool curCand[n];

    // põe todos os elementos da mask a falso
    for (int i = 0; i<n; i++) {
        curCand[i] = false;
    }



    while(true) {
        sum = 0;

        //testa a soma dos elementos ativos da mask ou seja A[i]só é somado se curCand[i] == true
        for (int i = 0; i < n; i++) {
            sum += A[i] * curCand[i];
        }

        //validação do resultado
        if(sum == T) {
            // sempre que se repete o ciclo tem que se colocar o tamanho da array de resultado a 0
            subsetSize = 0;

            /*ciclo para verificar quais os elementos colocados, corrigir o tamanho da array,
            * caso se usasse vetores bastava dar push
            */
            for (int j = 0; j < n; j++) {

                /*
                 * aumenta o tamanho do subset se CurCand[j] == true, e atribuí o valor da array no indice j
                 * ao subset no indice do subset atual
                 */
                if(curCand[j]){
                    subset[subsetSize++] = A[j];
                }

            }
            return true;
        }

        //coloca o indice a 0 sempre que se repete o ciclo
        int curIndex = 0;

        /* Move o indice atual da curCand para a frente
         * está tudo a falso inicialmente, logo não se inicia o ciclo da primeira vez
         * na segunda vez já temos o curCand[0] a verdadeiro, logo o indíce incrementa 1
         * */
        while(curCand[curIndex]) {
            curIndex = curIndex + 1;
            if (curIndex == n) {
                break;
            }
        }

        //para o ciclo se o indice atual da array curCand for igual ao tamanho da array original
        if(curIndex == n) {
            break;
        }

        //coloca a falso os valores de curCand até ao indice atual
        for(int k = 0; k < curIndex; k++) {
            curCand[k] = false;
        }

        // coloca o indice atual a true
        curCand[curIndex] = true;
    }




    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), false);
}