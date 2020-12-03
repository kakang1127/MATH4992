#include <iostream>
#include "block.h"
using namespace std;

class path{
    public:
        path(Block* start_block);
        path(path* p);
        path(path* p, Block* c_block,  int w);
        ~path();
        path* previousPath() const;
        void print() const;
        int getTotalWeight() const;
        Block* currentBlock() const;
        void reachEnd();
        bool getEnd() const;
        bool contains(int n) const;

    private:
        int step;
        int weight;
        int total_weight;
        Block* current;
        path* prev;
        bool end;
        int* containsBlock;
};