#include "path.h"

path::path(Block* start_block){
    step = 0;
    weight =0;
    total_weight = 0;
    prev = nullptr;
    current = start_block;
    start_block->visiting();
    end = 0;
    containsBlock = new int[step+1];
    containsBlock[0] = start_block->whatn();
};

path::path(path* p){
    step = p->step;
    weight = p->weight;
    total_weight = p->total_weight;
    prev = p->prev;
    current = p->current;
    end = p->end;
    containsBlock = new int[step+1];
    for (int i=0; i<step+1; i++){
        containsBlock[i] = p->containsBlock[i];
    }
};

path::path(path* p ,Block* c_block, int w){
    prev = p;
    current = c_block;
    c_block->visiting();
    step = p->step + 1;
    weight = w;
    total_weight = p->total_weight+w;
    end = 0;
    containsBlock = new int[step+1];
    for (int i=0; i<step; i++){
        containsBlock[i] = p->containsBlock[i];
    }
    containsBlock[step] = c_block->whatn();
};

path::~path(){
    if(containsBlock) delete[] containsBlock;
    if(current) delete current;
    if (prev) delete prev;
}

path* path::previousPath() const{
    if (this->prev != nullptr) return prev;
    else return 0;
};

void path::print() const{
    cout<<current->whatn()+1;
    if (prev==nullptr) cout<<endl;
    else {
        cout<<" <--["<<weight<<"]-- ";
        this->previousPath()->print();
    }
};

int path::getTotalWeight() const{
    return total_weight;
};

Block* path::currentBlock() const{
    return current;
};
void path::reachEnd(){
    end = 1;
};

bool path::getEnd() const{
    return end;
};

bool path::contains(int n) const{
    for (int i=0; i<step; i++) if (containsBlock[i]==n) return true;
    return false;
};