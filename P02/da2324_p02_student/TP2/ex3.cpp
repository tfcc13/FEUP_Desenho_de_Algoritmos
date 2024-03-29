// By: Gonçalo Leão

#include <climits>

unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // TODO

    bool curCand[n];
    int sum;
    int sumWeight;
    bool foundSol = false;
    int maxSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        curCand[i] = false;
    }

    while (true) {
        sum = 0;
        sumWeight = 0;
        for (int i = 0; i < n; i++) {
            sum = sum + values[i] * curCand[i];
            sumWeight += weights[i] * curCand[i];
        }

        if (sumWeight <= maxWeight) {
            if (sum >= maxSum || !foundSol ) {
                maxSum = sum;

                for (unsigned int k = 0; k < n; k++) {
                    usedItems[k] = curCand[k];
                }
///PORQUE È QUE PONDO FOUNDSOL RESULTA ? Deve ser do compilador
                foundSol = true;
            }

        }

        int curIndex = 0;

        while (curCand[curIndex]) {
            curIndex = curIndex + 1;
            if (curIndex == n) {
                break;
            }

        }

        if (curIndex == n) {
            break;
        }

        for (int k = 0; k < curIndex; k++) {
            curCand[k] = false;
        }

        curCand[curIndex] = true;


    }


    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}