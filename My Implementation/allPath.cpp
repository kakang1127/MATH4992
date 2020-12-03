#include "allPath.h"
#include <limits>

allPath::allPath(Block* start){
    size = 1;
    steps = 0;
    paths = new path*[size];
    paths[0] = new path(start);
};

allPath::~allPath(){
    if(paths){
    for (int i=0; i<size;i++) if(paths[i]) delete paths[i];
    delete[] paths;
    }
}

int allPath::getSize() const{
    return size;
};


int allPath::getStep() const{
    return steps;
};

int allPath::getShortestDistance() const{
    int min = paths[0]->getTotalWeight();

    for (int i=0; i<size; i++){ 
        if (min>paths[i]->getTotalWeight()) min =paths[i]->getTotalWeight();
    }

    return min;
};

int allPath::existEndPath() const{
    for (int i=0; i<size; i++){
        if (paths[i]->getEnd()) {
            //cout<<"exist end path"<<endl;
            return i;
        }
    }
    //cout<<"no end path"<<endl;
    return -1;
};

int allPath::endPathWithSD() const{
    int length = std::numeric_limits<int>::max();
    int ans = -1;
    for(int i = 0; i<size; i++){
        if (paths[i]->getEnd() && paths[i]->getTotalWeight()<length){ 
            length = paths[i]->getTotalWeight();
            ans = i;
        }
    }

    return ans;
};

void allPath::oneStepFurther(int** board, int boardSize, Block** Nodes, int end){
    //cout<<"oneStepFuther..."<<endl;
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
            if (board[paths[i]->currentBlock()->whatn()][j]!= 0 && paths[i]->contains(j)==0){
                directions++;
                walk[i][j] = 1;
            }
        }
    }
    
    path** newa = new path*[directions];
    int w = 0;
    for (int i=0; i<size; i++){
        if (paths[i]->getEnd()){
            newa[w++] = new path(paths[i]);
            continue;
        }
        for (int j=0; j<boardSize; j++){
            if (walk[i][j]){
                newa[w++] = new path(paths[i],Nodes[j], board[paths[i]->currentBlock()->whatn()][j]);
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

void allPath::print() const{
    cout<<"Current steps: "<<steps<<endl;
    cout<<"Current size: "<<size<<endl;
    for (int i=0; i<size; i++) {
        paths[i]->print();
        cout<<endl;
    }
};

void allPath::findShortestPath(int** board, int boardSize, Block** Nodes, int end){
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
    this->oneStepFurther(board, boardSize, Nodes, end);
    this->findShortestPath(board, boardSize, Nodes, end);
};