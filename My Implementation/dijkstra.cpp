#include <iostream>
#include <cmath>
#include "dijkstra.h"
using namespace std;

void dijkstra(int** board,int size, int start, int end){
    Block ** Nodes = new Block*[size];
    for (int i=0; i<size; i++){
        Nodes[i] = new Block(i);
    }

    allPath* a = new allPath(Nodes[start]);
    a->findShortestPath(board, size, Nodes, end);

    for (int i=0; i<size; i++) delete Nodes[i];
    delete[] Nodes;
};

int** random_symmetric_matrix(int size){
    int** board = new int* [size];

    for (int i=0; i<size; i++){
        board[i] = new int[size];
    }

    for (int i=0; i<size; i++){
        for (int j=i; j<size; j++){
            if (i==j) board[i][j] = board[j][i] = 0; 
            else if (i==0 ||  j== 0) board[i][j] = board[j][i] = 0; 
            else{
                int a = std::rand() % (2);
                if (a){
                    int temp = std::rand() % (10);
                    board[i][j] = board[j][i] = temp; 
                    }
                else board[i][j] = board[j][i] = 0; 
            }
        }   
    }

    return board;
};

