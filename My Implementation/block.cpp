#include "block.h"

Block:: Block(int n){
    visit = 0;
    number = n;
};


bool Block::visited() const{
    return visit;
};

int Block::whatn() const{
    return number;
};

void Block::visiting(){
    //cout<<"Visitng Block"<<number+1<<endl;
    visit = 1;
};


