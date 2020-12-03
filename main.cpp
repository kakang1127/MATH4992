#include <iostream>
#include <cmath>
#include "dijkstra.h"
//#include "dijkstra_new.h"
#include "online_source.h"
#include <chrono> 
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono; 


int main(){
    srand((unsigned) time(0));
/*    int size;

    cout<<"number of node: ";
    cin>>size;

    int** board = new int*[size];
    for (int i=0; i<size; i++){
        board[i] = new int[size];
    }
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            board[i][j] = 0;
        }   
    }
    
    bool addRelation = 1;

    while(addRelation){
        bool ans;
        cout<<"Add relationship between nodes? (Yes = 1 /N = 0)";
        cin>> ans;
        if (ans == 0) break;
        int first, second, weight;
        cout<<"first node: ";
        cin>> first;
        cout<<"second node: ";
        cin>> second;
        cout<<"weight: ";
        cin>> weight;

        board[first-1][second-1] = board[second-1][first-1] = weight;
    }
*/
ofstream implement1; implement1.open("implement1.csv");
ofstream online; online.open("online.csv");
    int size = 1000;
    implement1<<size;
    online<<size;
    
for (int i=0; i<10; i++){


    int** board = random_symmetric_matrix(size);

/*  for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl;
    } 

    int start, end;
    cout<<"Which node is the start node? (enter a integer) ";
    cin>> start;
    cout<<"Which node is the end node? (enter a integer) ";   
    cin>> end;
*/


    auto start_time_1 = high_resolution_clock::now(); 

    
    dijkstra(board,size, 0, size-1);


    auto stop_time_1 = high_resolution_clock::now(); 

    auto duration_1 = duration_cast<microseconds>(stop_time_1 - start_time_1); 
  
    cout << "Time taken by my implement1ation: "
         << duration_1.count() << " microseconds" << endl; 

    implement1<<","<<duration_1.count();

    auto start_time_2 = high_resolution_clock::now(); 

    online_source(board, size, 0, size-1);


    auto stop_time_2 = high_resolution_clock::now(); 

    auto duration_2 = duration_cast<microseconds>(stop_time_2 - start_time_2); 
  
    cout << "Time taken by online source code: "
         << duration_2.count() << " microseconds" << endl; 

    online<<","<< duration_2.count(); 


    if(board){
    for(int i=0; i<size; i++) if(board[i]) delete[] board[i];
    delete[] board;
    }
    
}
    implement1<<endl;
    online<<endl;

    implement1.close();
    online.close();


    return 0;
}