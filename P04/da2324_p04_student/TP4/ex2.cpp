#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include "exercises.h"


void moveHanoi(int n, char src, char dest, char aux, std::string &moves) {

    if (n == 1) {
        // caso base em que só há um disco para mover
        moves += src;
        moves += "->";
        moves += dest;
        moves += ',';
    } else {
        //move do src para a pega auxiliar usando o dest como auxiliar
        moveHanoi(n-1,src,aux,dest, moves);
        moves += src;
        moves += "->";
        moves += dest;
        moves += ',';

        //move do auxiliar para a pega de destino usand o src ocmo auxiliar
        moveHanoi(n-1,aux,dest,src, moves);
    }
}


std::string hanoiDC(unsigned int n, char src, char dest) {
    std::string moves = "";

    moveHanoi(n, src, dest, 'C', moves);
    moves.pop_back();
    return moves;



}





/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, testHanoi_height4) {
    std::string moves = hanoiDC(4, 'A', 'B');
    EXPECT_EQ(std::count(moves.begin(),moves.end(),','),14); // there are 15 moves
    EXPECT_EQ(moves,"A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}