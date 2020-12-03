#include<iostream>
#include<stdio.h>
#include <limits.h> 
#include "online_source.h"
using namespace std;

void online_source(int** G,int size,int start, int end) {
    int cost[size][size],distance[size],pred[size];
    int visited[size],count,mindistance,nextnode,i,j;
    for(i=0;i<size;i++)
        for(j=0;j<size;j++){
            if(G[i][j]==0)
                cost[i][j]=99999999;
            else
                cost[i][j]=G[i][j];
        }
    
    for(i=0;i<size;i++) {
            distance[i]=cost[start][i];
            pred[i]=start;
            visited[i]=0;
    }
    distance[start]=0;
    visited[start]=1;
    count=1;
    while(count<size-1) {
        mindistance=99999999;
        for(i=0;i<size;i++)
            if(distance[i]<mindistance && !visited[i]) {
                mindistance=distance[i];
                nextnode=i;
            }
        
        visited[nextnode]=1;

        for(i=0;i<size;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i]) {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        count++;
    }

    cout<<"Distance of node"<<end+1<<" = "<<distance[end]<<endl;
    cout<<"Path="<<end+1;
    j=end;
    do {
        j=pred[j];
        cout<<"<-"<<j+1;
    }while(j!=start);
    cout<<endl;

}