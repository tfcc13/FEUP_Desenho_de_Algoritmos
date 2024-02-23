// By: Gonçalo Leão
// With contributions by Eduardo Almeida

#include <climits>

// Tem uma complexidade n^3
int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {

    int maxSum = INT_MIN;
    int sum;
    bool firstSum = true;
    for (int a = 0; a < n; a++ ) {
        for(int b = a; b < n; b++) {
            sum = 0;

            for (int c = a; c <= b; c++) {
                sum += A[c];
            }

            if(firstSum) {
                firstSum = false;
                maxSum = sum;
                i = a;
                j = b;
            }
            else if (sum > maxSum) {
                maxSum = sum;
                i = a;
                j = b;
            }
        }

    }

    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}