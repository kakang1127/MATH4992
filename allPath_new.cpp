#include "allPath_new.h"
#include <limits>

allPath_new::allPath_new(int start){
    size = 1;
    steps = 0;
    path_new** paths = new path_new*[size];
    paths[0] = new path_new(start);
};

allPath_new::~allPath_new(){
/*    if(paths){
    for (int i=0; i<size;i++) if(paths[i]) delete paths[i];
    delete[] paths;
    }*/
}

int allPath_new::getSize() const{
    return size;
};


int allPath_new::getStep() const{
    return steps;
};

int allPath_new::getShortestDistance() const{
    int min = paths[0]->getTotalWeight();

    for (int i=0; i<size; i++){ 
        if (min>paths[i]->getTotalWeight()) min =paths[i]->getTotalWeight();
    }

    return min;
};

int allPath_new::existEndPath() const{
    for (int i=0; i<size; i++){
        cout<<i<<"\n";
        cout<<paths[i]->getEnd()<<endl;
        if (paths[i]->getEnd()) {
            //cout<<"exist end path"<<endl;
            return i;
        }
    }
    //cout<<"no end path"<<endl;
    return -1;
};

int allPath_new::endPathWithSD() const{
    int length = 99999999;
    int ans = -1;
    for(int i = 0; i<size; i++){
        if (paths[i]->getEnd() && paths[i]->getTotalWeight()<length){ 
            length = paths[i]->getTotalWeight();
            ans = i;
        }
    }

    return ans;
};

void allPath_new::oneStepFurther(int** board, int boardSize, int end){
    cout<<"oneStepFuther..."<<endl;
    int directions = 0;
    bool walk[size][boardSize];

    for (int i=0; i<size; i++){
        for (int j=0; j<boardSize; j++){
            walk[i][j] = 0;
        }   
    }

    for (int i=0; i<size; i++){
        if (paths[i]->getEnd()){
            directions++;
            continue;
        }
        for (int j=0; j<boardSize; j++){
            if (board[paths[i]->currentBlock()][j]!= 0 && paths[i]->contains(j)==0){
                directions++;
                walk[i][j] = 1;
            }
        }
    }
    
    path_new** newa = new path_new*[directions];
    int w = 0;
    for (int i=0; i<size; i++){
        if (paths[i]->getEnd()){
            newa[w++] = new path_new(paths[i]);
            continue;
        }
        for (int j=0; j<boardSize; j++){
            if (walk[i][j]){
                newa[w++] = new path_new(paths[i],j, board[paths[i]->currentBlock()][j]);
                if (j == end) newa[w-1]->reachEnd();
            }
        }
    }

    steps++;
    //path** temp = paths;
    paths = newa;
    /*for (int i=0; i<size; i++){
        delete temp[i];
    }
    delete[] temp;*/
    size=directions;
    //this->print();
};

void allPath_new::print() const{
    cout<<"Current steps: "<<steps<<endl;
    cout<<"Current size: "<<size<<endl;
    for (int i=0; i<size; i++) {
        paths[i]->print();
        cout<<endl;
    }
};

void allPath_new::findShortestPath(int** board, int boardSize, int end){
    if (size == 0) {
        cout<<"Does not exist any path!"<<endl;
        return;
    }
    if (this->existEndPath()!=-1){
        if(paths[this->endPathWithSD()]->getTotalWeight()==this->getShortestDistance()){ 
            cout<<"Shorest Path:"<<endl;
            paths[this->endPathWithSD()]->print();
            cout<<"Weighted length: "<<paths[this->endPathWithSD()]->getTotalWeight()<<endl;
            return;
        }
    }

    cout<<"??"<<endl;
    this->oneStepFurther(board, boardSize, end);
    this->findShortestPath(board, boardSize, end);
};