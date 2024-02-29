// By: Gonçalo Leão

#include <algorithm>
#include <vector>

using namespace std;

struct Item {
    unsigned int v;
    unsigned int w;
    double r;

};

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {

    vector<Item> allItems;

    for (int i = 0; i < n; i++) {
        Item currItem = {values[i],weights[i],(double)values[i]/weights[i]};
        allItems.push_back(currItem);
    }

    std::sort(allItems.begin(), allItems.end(), [](const Item& item1, const Item& item2) {
        return item1.r>item2.r;
    });


    double weight = 0;
    double value = 0;
    unsigned int currItem = 0;

    while(weight < maxWeight) {
        if(weight+allItems[currItem].w <= maxWeight) {
            usedItems[currItem] = 1;
            weight = weight + allItems[currItem].w;
            value = value + allItems[currItem].v;
        }

        else {
            usedItems[currItem] = (maxWeight-weight) / allItems[currItem].w;
            value = value + usedItems[currItem]*allItems[currItem].v;
            weight = maxWeight;
        }
        currItem++;
    }

    return value;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}